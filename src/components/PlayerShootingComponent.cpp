#include <cassert>
#include <iostream>

#include "components/PlayerShootingComponent.hpp"
#include "Projectiles.hpp"

PlayerShootingComponent::PlayerShootingComponent(
    PlayerInputComponent *input,
    Object *weapon1Muzzle,
    Object *weapon1Timer,
    Object *map)
    : input(input)
{
    assert(input != nullptr && "Missing input component");

    assert(weapon1Muzzle != nullptr && "Missing weapon1Muzzle component");

    weapon1MuzzleTransform = weapon1Muzzle->getChild<TransformComponent>();
    assert(weapon1MuzzleTransform != nullptr && "Missing weapon1Muzzle transform component");

    assert(weapon1Timer != nullptr && "Missing weapon1Timer component");

    weapon1TimerComponent = weapon1Timer->getChild<TimerComponent>();
    assert(weapon1TimerComponent != nullptr && "Missing weapon1Timer timer component");

    weapon1TimerComponent->setTimeout(weapon1Delay);

    assert(map != nullptr && "Missing map object");

    projectiles = map->getChildByName("Projectiles");
    assert(projectiles != nullptr && "Missing Projectiles object");
}

void PlayerShootingComponent::update(float)
{
    if (input->shootWeapon1)
    {
        if (weapon1TimerComponent->isRunning())
        {
            return;
        }

        weapon1TimerComponent->start();

        auto bullet = spaceshooter::projectiles::createBullet(weapon1MuzzleTransform->getGlobalPosition(), Vector(0.0, -1.0), true);

        projectiles->addChild(bullet);
    }

    if (input->shootWeapon2)
    {
        std::cout << "Firing weapon 2!" << std::endl;
    }
}