#include "enemies/Astroid.hpp"
#include "Config.hpp"

Astroid::Astroid(Vector position) : Enemy(position, Vector(0, 1))
{
    speed = 150.0;
    health = 10.0;
}

Astroid::~Astroid() {}

void Astroid::init()
{
    loadEntities();

    createVisuals();
}

void Astroid::loadEntities()
{
    destroyTimer = Game::create<Timer>(destroyTime);
    destroyTimer->setName("DestroyTimer");
    destroyTimer->start();

    destroyTimer->setCallback([this](void *)
                              { destroyCallback(); });

    addChild(destroyTimer);

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
    Vector newPosition = getPosition() + velocity * speed * dt;

    setPosition(newPosition);
}

void Astroid::destroyCallback()
{
    queueDelete();
}