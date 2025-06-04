#pragma once

#include <jengine/jengine.hpp>
#include "components/PlayerInputComponent.hpp"

class PlayerMovementComponent : public Component
{
public:
    float maxSpeed = 500.0;
    float accelerationRate = 3000.0f;
    float friction = 1200.0f;

    PlayerMovementComponent(TransformComponent *transform, PhysicsComponent *physics, PlayerInputComponent *input);

    void update(float dt) override;

private:
    TransformComponent *transform = nullptr;
    PhysicsComponent *physics = nullptr;
    PlayerInputComponent *input = nullptr;

    void clampPosition();
};
