#pragma once

#include <jengine/jengine.hpp>
#include "components/PlayerInputComponent.hpp"

class PlayerShootingComponent : public Object
{
public:
    PlayerShootingComponent(
        PlayerInputComponent *input,
        Object *map,
        Vector muzzlePosition,
        float weaponSpeed);

    void update(float dt) override;

private:
    PlayerInputComponent *input = nullptr;

    TransformComponent *weaponMuzzleTransform = nullptr;

    TimerComponent *weaponTimerComponent = nullptr;

    Object *projectiles = nullptr;
};