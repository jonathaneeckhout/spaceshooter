#pragma once

#include <jengine/jengine.hpp>

class EnemyShootComponent : public Object
{
public:
    EnemyShootComponent(Vector muzzlePosition, float weaponSpeed);

    void update(float dt) override;

private:
    TransformComponent *weaponMuzzleTransform = nullptr;

    TimerComponent *weaponTimerComponent = nullptr;

    Object *projectiles = nullptr;
};
