#include <cassert>

#include "components/LootComponent.hpp"

LootComponent::LootComponent(TransformComponent *transform, HealthComponent *health) : transform(transform)
{
    assert(transform != nullptr && "Missing transform component");
    assert(health != nullptr && "Missing score component");

    std::function<void(Object *)> handler = [this](Object *source)
    {
        onDeath(source);
    };

    health->addEventHandler<Object *>("onDeath", handler);
}

void LootComponent::setLoot(std::function<Object *(Vector)> lootFactoryFunction, float chance)
{
    dropLoot = lootFactoryFunction;
    dropChance = chance;
}

void LootComponent::onDeath(Object *)
{
    if (dropLoot == nullptr)
    {
        return;
    }

    if (!Game::getInstance()->shouldHappen(dropChance))
    {
        return;
    }

    auto loot = dropLoot(transform->getPosition());

    // (this) LootComponent // (parent) Enemy // (parent) Entities // (parent) Map // (child) Powerups
    auto powerUps = getParent()->getParent()->getParent()->getChildByName("Powerups");

    powerUps->addChild(loot);
}