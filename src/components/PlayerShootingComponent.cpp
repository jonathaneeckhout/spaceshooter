#include <cassert>
#include <iostream>

#include "components/PlayerShootingComponent.hpp"
#include "factories/Projectiles.hpp"

PlayerShootingComponent::PlayerShootingComponent(
    PlayerInputComponent *input,
    Object *map,
    Vector muzzlePosition,
    float weaponSpeed)
    : input(input)
{
    assert(input != nullptr && "Missing input component");

    assert(map != nullptr && "Missing map object");

    projectiles = map->getChildByName("Projectiles");
    assert(projectiles != nullptr && "Missing Projectiles object");

    weaponMuzzleTransform = new TransformComponent(muzzlePosition);
    addChild(weaponMuzzleTransform);

    weaponTimerComponent = new TimerComponent(weaponSpeed, false);
    addChild(weaponTimerComponent);
}

void PlayerShootingComponent::update(float)
{
    if (input->shoot)
    {
        if (weaponTimerComponent->isRunning())
        {
            return;
        }

        weaponTimerComponent->start();

        auto bullet = spaceshooter::projectiles::createBullet(weaponMuzzleTransform->getGlobalPosition(), Vector(0.0, -1.0), true);

        projectiles->addChild(bullet);
    }
}