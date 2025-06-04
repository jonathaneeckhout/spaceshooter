#include <cassert>

#include "components/PlayerMovementComponent.hpp"

PlayerMovementComponent::PlayerMovementComponent(
    TransformComponent *transform,
    PhysicsComponent *physics,
    PlayerInputComponent *input)
    : transform(transform),
      physics(physics),
      input(input)
{
    assert(transform != nullptr && "Missing transform component");
    assert(physics != nullptr && "Missing physics component");
    assert(input != nullptr && "Missing input component");
}

void PlayerMovementComponent::update(float dt)
{
    Vector inputDirection;
    if (input->moveLeft)
    {
        inputDirection.x -= 1;
    }
    if (input->moveRight)
    {
        inputDirection.x += 1;
    }
    if (input->moveUp)
    {
        inputDirection.y -= 1;
    }
    if (input->moveDown)
    {
        inputDirection.y += 1;
    }

    if (inputDirection.magnitude() > 0)
    {
        inputDirection = inputDirection.normalize();

        transform->velocity += inputDirection * accelerationRate * dt;
    }
    else
    {
        if (transform->velocity.magnitude() > 0)
        {
            Vector frictionForce = -transform->velocity.normalize() * friction * dt;
            if (frictionForce.magnitude() > transform->velocity.magnitude())
                transform->velocity = Vector();
            else
                transform->velocity += frictionForce;
        }
    }

    if (transform->velocity.magnitude() > maxSpeed)
    {
        transform->velocity = transform->velocity.normalize() * maxSpeed;
    }

    physics->moveAndStop(dt);

    clampPosition();
}

void PlayerMovementComponent::clampPosition()
{
    Vector pos = transform->getPosition();

    Vector windowSize = Game::getInstance()->renderer->getWindowSize();

    pos.x = std::clamp<float>(pos.x, 0.0, windowSize.x);
    pos.y = std::clamp<float>(pos.y, 0.0, windowSize.y - 96.0);

    transform->setPosition(pos);
}
