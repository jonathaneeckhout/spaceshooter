#include "projectiles/player/Bullet.hpp"
#include "enemies/Enemy.hpp"
#include "Config.hpp"

Bullet::Bullet(Vector position, Vector direction) : Entity(position)
{
    velocity = direction.normalize();
}

Bullet::~Bullet() {}

void Bullet::init()
{
    destroyTimer = Game::create<Timer>(destroyTime);
    destroyTimer->setName("DestroyTimer");
    destroyTimer->start();

    destroyTimer->setCallback([this](void *)
                              { destroyCallback(); });

    addChild(destroyTimer);

    auto collisionShape = Game::create<CollisionShapeSquare>(Vector(-2, -2), Vector(4, 4));
    collisionShape->setName("CollisionShape");

    collisionShape->inLayer = Config::NoCollisionLayer;
    collisionShape->viewLayer = Config::EnemyCollisionLayer;

    collisionShape->collisionStartHandlers.push_back([this](CollisionShape *shape)
                                                     { handleCollisiontStarted(shape); });

    addChild(collisionShape);

    createVisuals();

    Game::getInstance()->mixer->playSound("bullet");
}

void Bullet::update(float dt)
{
    Vector newPosition = getPosition() + velocity * speed * dt;
    setPosition(newPosition);
}

void Bullet::createVisuals()
{
    auto body = Game::create<Square>(Vector{-2, -2}, Vector(4.0, 8.0));

    body->setColor(0xA0, 0xFC, 0x24, 255);

    addChild(body);
}

void Bullet::destroyCallback()
{
    queueDelete();
}

void Bullet::handleCollisiontStarted(CollisionShape *shape)
{

    auto enemy = dynamic_cast<Enemy *>(shape->getParent());
    if (enemy == nullptr)
    {
        return;
    }

    enemy->hurt(damage);

    Game::getInstance()->mixer->playSound("bulletImpact");

    queueDelete();
}
