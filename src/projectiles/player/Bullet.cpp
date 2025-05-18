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

    collisionShape->collisionStartHandlers.push_back([this](std::weak_ptr<CollisionShape> shape)
                                                     { handleCollisiontStarted(shape); });

    addChild(collisionShape);

    createVisuals();
}

void Bullet::update(float dt)
{
    Vector newPosition = getPosition() + velocity * speed * dt;
    setPosition(newPosition);
}

void Bullet::createVisuals()
{
    auto body = Game::create<Square>(Vector{-2, -2}, 4, 8);

    body->color = {0xA0, 0xFC, 0x24, 255};

    addChild(body);
}

void Bullet::destroyCallback()
{
    queueDelete();
}

void Bullet::handleCollisiontStarted(std::weak_ptr<CollisionShape> shape)
{
    auto shapePtr = shape.lock();
    if (!shapePtr)
    {
        return;
    }

    auto shapeParent = shapePtr->getParent();

    auto shapeParentPtr = shapeParent.lock();
    if (!shapeParentPtr)
    {
        return;
    }

    Enemy *enemy = dynamic_cast<Enemy *>(shapeParentPtr.get());
    if (enemy == nullptr)
    {
        return;
    }

    enemy->hurt(damage);

    queueDelete();
}
