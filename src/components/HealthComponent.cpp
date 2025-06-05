#include <algorithm>

#include "components/HealthComponent.hpp"

HealthComponent::HealthComponent(float health) : health(health), maxHealth(health)
{
    events.createEvent<float>("onChanged");
    events.createEvent<Object *>("onDeath");
}

void HealthComponent::setHealth(float value, Object *source)
{
    float diff = value - health;

    health = value;

    health = std::clamp<float>(health, 0.0, maxHealth);

    if (health <= 0.0)
    {
        getParent()->queueDelete();

        events.trigger<Object *>("onDeath", source);
    }

    events.trigger<float>("onChanged", diff);
}

void HealthComponent::setMaxHealth(float value)
{
    maxHealth = value;

    health = std::clamp<float>(health, 0.0, maxHealth);
}

void HealthComponent::heal(float value, Object *source)
{
    setHealth(health + value, source);
}

void HealthComponent::hurt(float value, Object *source)
{
    setHealth(health - value, source);
}
