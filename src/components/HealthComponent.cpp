#include <algorithm>

#include "components/HealthComponent.hpp"

HealthComponent::HealthComponent(float health) : health(health), maxHealth(health)
{
    events.createEvent<float>("onChanged");
}

void HealthComponent::setHealth(float value)
{
    float diff = value - health;

    health = value;

    health = std::clamp<float>(health, 0.0, maxHealth);

    if (health <= 0.0)
    {
        getParent()->queueDelete();
    }

    events.trigger<float>("onChanged", diff);
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
