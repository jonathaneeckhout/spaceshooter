#pragma once

#include <jengine/jengine.hpp>
#include "components/PlayerInputComponent.hpp"

class PlayerShootingComponent : public Component
{
public:
    PlayerShootingComponent(
        PlayerInputComponent *input,
        Object *weapon1Muzzle,
        Object *weapon1Timer,
        Object *map);

    void update(float dt) override;

private:
    PlayerInputComponent *input = nullptr;

    TransformComponent *weapon1MuzzleTransform = nullptr;

    TimerComponent *weapon1TimerComponent = nullptr;

    Object *projectiles = nullptr;

    float weapon1Delay = 0.2;
};