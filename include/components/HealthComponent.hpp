#pragma once

#include <jengine/jengine.hpp>

class HealthComponent : public Object
{
public:
    HealthComponent(float health);

    float getHealth() { return health; };
    void setHealth(float value, Object *source);

    float getMaxHealth() { return maxHealth; };
    void setMaxHealth(float value);

    void heal(float value, Object *source);
    void hurt(float value, Object *source);

private:
    float health = 0.0;
    float maxHealth = 0.0;
};