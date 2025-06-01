#pragma once

#include <jengine/jengine.hpp>

class HealthBar : public Entity
{
public:
    HealthBar(Vector position, float health, float maxHealth);
    ~HealthBar();

    void init() override;

    void output() override;

    void setHealth(float value);

private:
    float health = 0.0;
    float maxHealth = 0.0;

    float width = 124.0;

    Square *backgroundBar = nullptr;

    Square *bar = nullptr;

    void createVisuals();
};