#include "projectiles/enemies/Zap.hpp"
#include "Config.hpp"

Zap::Zap(Vector position, Vector direction) : Entity(position)
{
    velocity = direction.normalize();
}

Zap::~Zap() {}

void Zap::init()
{
    destroyTimer = Game::create<Timer>(destroyTime);
    destroyTimer->setName("DestroyTimer");
    destroyTimer->start();

    destroyTimer->setCallback([this](void *)
                              { destroyCallback(); });

    addChild(destroyTimer);

    auto collisionShape = Game::create<CollisionShapeSquare>(Vector(-4, -4), Vector(8, 8));
    collisionShape->setName("CollisionShape");

    collisionShape->inLayer = Config::NoCollisionLayer;
    collisionShape->viewLayer = Config::PlayerCollisionLayer;

    collisionShape->collisionStartHandlers.push_back([this](std::weak_ptr<CollisionShape> shape)
                                                     { handleCollisiontStarted(shape); });

    addChild(collisionShape);

    createVisuals();
}

void Zap::update(float dt)
{
    Vector newPosition = getPosition() + velocity * speed * dt;
    setPosition(newPosition);
}

void Zap::createVisuals()
{
    auto body = Game::create<Square>(Vector{-2, -2}, 8, 8);

    body->color = {0xAA, 0x22, 0xCC, 255};

    addChild(body);
}

void Zap::destroyCallback()
{
    queueDelete();
}

void Zap::handleCollisiontStarted(std::weak_ptr<CollisionShape> shape)
{
}