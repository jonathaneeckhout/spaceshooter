#include <cassert>

#include "components/EnemyShootComponent.hpp"
#include "factories/Projectiles.hpp"
#include "Spaceshooter.hpp"

EnemyShootComponent::EnemyShootComponent(Vector muzzlePosition, float weaponSpeed)
{
    Object *map = Spaceshooter::getInstance()->getMap();

    assert(map != nullptr && "Missing map object");

    projectiles = map->getChildByName("Projectiles");
    assert(projectiles != nullptr && "Missing Projectiles object");

    weaponMuzzleTransform = new TransformComponent(muzzlePosition);
    addChild(weaponMuzzleTransform);

    weaponTimerComponent = new TimerComponent(weaponSpeed, false);
    addChild(weaponTimerComponent);
}

void EnemyShootComponent::update(float)
{

    if (weaponTimerComponent->isRunning())
    {
        return;
    }

    weaponTimerComponent->start();

    if (Spaceshooter::getInstance()->getPlayer() == nullptr)
    {
        return;
    }

    Vector direction = Spaceshooter::getInstance()->directionToPlayer(weaponMuzzleTransform->getGlobalPosition());

    auto bullet = spaceshooter::projectiles::createBullet(weaponMuzzleTransform->getGlobalPosition(), direction, false);

    projectiles->addChild(bullet);
}