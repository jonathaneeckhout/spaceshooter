#include <cassert>

#include "components/ProjectileComponent.hpp"

ProjectileComponent::ProjectileComponent(
    TransformComponent *transform,
    float speed,
    float damage)
    : transform(transform),
      speed(speed),
      damage(damage)
{
    assert(transform != nullptr && "Missing transform component");
}

void ProjectileComponent::update(float dt)
{
    Vector newPosition = transform->getPosition() + transform->velocity * speed * dt;
    transform->setPosition(newPosition);
}