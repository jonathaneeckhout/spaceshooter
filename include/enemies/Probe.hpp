#pragma once

#include "enemies/Enemy.hpp"

class Probe : public Enemy
{
public:
    Probe(Vector position);
    ~Probe();

    void init() override;

    void update(float dt) override;

private:
    float weaponDelay = 1.5;

    Timer *weaponTimer = nullptr;

    void loadEntities();
    void createVisuals();

    void updateMovement(float dt);
    void updateShooting(float);
};
