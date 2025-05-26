#include "powerups/Powerup.hpp"
#include "Config.hpp"

Powerup::Powerup(Vector position) : Entity(position, Vector(0, 1)) {}

Powerup::~Powerup() {}

void Powerup::update(float dt)
{
    Vector newPosition = getPosition() + velocity * speed * dt;

    setPosition(newPosition);
}

void Powerup::init()
{
    loadEntities();
    createVisuals();
}

void Powerup::loadEntities()
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
    collisionShape->viewLayer = Config::PowerupCollisionLayer;

    collisionShape->collisionStartHandlers.push_back([this](std::weak_ptr<CollisionShape> shape)
                                                     { handleCollisiontStarted(shape); });

    addChild(collisionShape);
}

void Powerup::createVisuals() {}

void Powerup::applyEffect(std::shared_ptr<Player>) {}

void Powerup::destroyCallback()
{
    queueDelete();
}

void Powerup::handleCollisiontStarted(std::weak_ptr<CollisionShape> shape)
{
    auto shapePtr = shape.lock();
    if (!shapePtr)
    {
        return;
    }

    auto player = Game::safeCast<Player>(shapePtr->getParent());
    if (player == nullptr)
    {
        return;
    }

    applyEffect(player);

    Mixer::getInstance()->playSound("powerup");

    queueDelete();
}
