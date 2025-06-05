#include <algorithm>

#include "components/HealthComponent.hpp"

HealthComponent::HealthComponent(float health) : health(health), maxHealth(health) {}

void HealthComponent::setHealth(float value)
{
    health = value;

    health = std::clamp<float>(health, 0.0, maxHealth);
}

void HealthComponent::setMaxHealth(float value)
{
    maxHealth = value;

    health = std::clamp<float>(health, 0.0, maxHealth);
}

void HealthComponent::heal(float value)
{
    setHealth(health + value);
}

void HealthComponent::hurt(float value)
{
    setHealth(health - value);
}
