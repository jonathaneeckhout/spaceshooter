#pragma once

#include <jengine/jengine.hpp>

class HealthComponent : public Object
{
public:
    HealthComponent(float health);

    float getHealth() { return health; };
    void setHealth(float value);

    float getMaxHealth() { return maxHealth; };
    void setMaxHealth(float value);

    void heal(float value);
    void hurt(float value);

private:
    float health = 0.0;
    float maxHealth = 0.0;
};