#include <cassert>

#include "components/ProjectileComponent.hpp"
#include "components/HealthComponent.hpp"

ProjectileComponent::ProjectileComponent(
    TransformComponent *transform,
    CollisionComponent *collision,
    float speed,
    float damage)
    : transform(transform),
      speed(speed),
      damage(damage)
{
    assert(transform != nullptr && "Missing transform component");
    assert(collision != nullptr && "Missing collision component");

    std::function<void(Object *, bool)> handler = [this](Object *object, bool collides)
    {
        onCollision(object, collides);
    };

    collision->addEventHandler<Object *, bool>("onCollision", handler);
}

void ProjectileComponent::update(float dt)
{
    Vector newPosition = transform->getPosition() + transform->velocity * speed * dt;
    transform->setPosition(newPosition);
}

void ProjectileComponent::onCollision(Object *object, bool collides)
{
    if (!collides)
    {
        return;
    }

    auto health = object->getChild<HealthComponent>();
    if (health != nullptr)
    {
        health->hurt(damage, getParent());
    }

    getParent()->queueDelete();
}