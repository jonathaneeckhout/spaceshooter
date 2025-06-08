#include <cassert>

#include "components/LootBehaviorComponent.hpp"
#include "components/HealthComponent.hpp"

LootBehaviorComponent::LootBehaviorComponent(
    TransformComponent *transform,
    CollisionComponent *collision,
    float healing,
    float speed)
    : transform(transform),
      healing(healing),
      speed(speed)
{
    assert(transform != nullptr && "Missing transform component");
    assert(collision != nullptr && "Missing collision component");

    std::function<void(Object *, bool)> handler = [this](Object *object, bool collides)
    {
        onCollision(object, collides);
    };

    collision->addEventHandler<Object *, bool>("onCollision", handler);
}

void LootBehaviorComponent::update(float dt)
{
    Vector newPosition = transform->getPosition() + transform->velocity * speed * dt;
    transform->setPosition(newPosition);
}

void LootBehaviorComponent::onCollision(Object *object, bool collides)
{
    if (!collides)
    {
        return;
    }

    auto health = object->getChild<HealthComponent>();
    if (health != nullptr)
    {
        health->heal(healing, getParent());
    }

    getParent()->queueDelete();
}