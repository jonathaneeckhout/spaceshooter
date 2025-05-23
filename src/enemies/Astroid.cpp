#include "enemies/Astroid.hpp"
#include "Config.hpp"
#include "powerups/HealthPack.hpp"

Astroid::Astroid(Vector position) : Enemy(position, Vector(0, 1))
{
    speed = 150.0;
    health = 10.0;
    score = 5;
}

Astroid::~Astroid() {}

void Astroid::init()
{
    loadEntities();

    createVisuals();
}

void Astroid::loadEntities()
{
    collisionShape = Game::create<CollisionShapeSquare>(Vector(-16, -16), Vector(32, 32));
    collisionShape->setName("CollisionShape");

    collisionShape->inLayer = Config::EnemyCollisionLayer;
    collisionShape->viewLayer = Config::PlayerCollisionLayer;

    addChild(collisionShape);
}

void Astroid::createVisuals()
{
    auto body = Game::create<Square>(Vector{-16, -16}, 32, 32);

    body->color = {0x5A, 0x55, 0x4C, 255};

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
    // TODO: make random drop rate
    auto healthPack = Game::create<HealthPack>(getPosition());

    auto map = getMap();

    map->addPowerup(healthPack);
}