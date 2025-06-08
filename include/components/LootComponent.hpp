#pragma once

#include <functional>

#include <jengine/jengine.hpp>
#include "components/HealthComponent.hpp"

class LootComponent : public Object
{
public:
    LootComponent(TransformComponent *transform, HealthComponent *health);

    void setLoot(std::function<Object *(Vector)> lootFactoryFunction, float chance);

private:
    TransformComponent *transform;
    std::function<Object *(Vector)> dropLoot = nullptr;
    float dropChance = 0.0;

    void onDeath(Object *source);
};