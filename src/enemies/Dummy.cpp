#include "enemies/Dummy.hpp"
#include "Config.hpp"

Dummy::Dummy(Vector position) : Enemy(position, Vector(0, 1))
{
    speed = 150.0;
    health = 10.0;
}

Dummy::~Dummy() {}

void Dummy::init()
{
    loadEntities();

    createVisuals();
}

void Dummy::loadEntities()
{
    collisionShape = Game::create<CollisionShapeSquare>(Vector(-16, -16), Vector(32, 32));
    collisionShape->setName("CollisionShape");

    collisionShape->inLayer = Config::WorldCollisionLayer | Config::EnemyCollisionLayer;
    collisionShape->viewLayer = Config::PlayerCollisionLayer;

    addChild(collisionShape);
}

void Dummy::createVisuals()
{
    auto body = Game::create<Square>(Vector{-16, -16}, 32, 32);

    body->color = {0x5A, 0x55, 0x4C, 255};

    addChild(body);
}

void Dummy::update(float)
{
}
