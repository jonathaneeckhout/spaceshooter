#pragma once

#include "enemies/Enemy.hpp"

class Disc : public Enemy
{
public:
    Disc(Vector position);
    ~Disc();

    void init() override;

    void update(float dt) override;

private:
    float weaponDelay = 1.0;

    std::shared_ptr<Timer> weaponTimer;

    void loadEntities();
    void createVisuals();

    void updateMovement(float dt);
    void updateShooting(float);
};