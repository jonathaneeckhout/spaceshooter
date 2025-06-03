#include "enemies/Astroid.hpp"
#include "Config.hpp"
#include "powerups/HealthPack.hpp"

Astroid::Astroid(Vector position) : Enemy(position, Vector(0, 1))
{
    speed = 400.0;
    health = 20.0;
    score = 5;
}

Astroid::~Astroid() {}

void Astroid::init()
{
    loadEntities();

    createVisuals();
}

void Astroid::cleanup() {}

void Astroid::loadEntities()
{
    collisionShape = Game::create<CollisionShapeSquare>(Vector(-32, -32), Vector(96, 96));
    collisionShape->setName("CollisionShape");

    collisionShape->inLayer = Config::EnemyCollisionLayer;
    collisionShape->viewLayer = Config::PlayerCollisionLayer;

    collisionShape->collisionStartHandlers.push_back([this](CollisionShape *shape)
                                                     { handleCollisiontStarted(shape); });

    addChild(collisionShape);
}

void Astroid::createVisuals()
{
    auto body = Game::create<Square>(Vector{-32, -32}, Vector(64.0, 64.0));

    body->setColor(0x5A, 0x55, 0x4C, 255);

    addChild(body);
}

void Astroid::update(float dt)
{
    if (deleteOffscreen())
    {
        return;
    }

    Vector newPosition = getPosition() + velocity * speed * dt;

    setPosition(newPosition);
}

void Astroid::dropLoot()
{
    if (!Game::getInstance()->shouldHappen(0.1))
    {
        return;
    }

    auto healthPack = Game::create<HealthPack>(getPosition());

    auto map = getMap();

    map->addPowerup(healthPack);
}

void Astroid::handleCollisiontStarted(CollisionShape *shape)
{
    auto player = dynamic_cast<Player *>(shape->getParent());
    if (player == nullptr)
    {
        return;
    }

    player->hurt(collisionDamage);

    Game::getInstance()->mixer->playSound("ZapImpact");

    queueDelete();
}
