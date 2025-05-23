#pragma once

#include "powerups/Powerup.hpp"

class HealthPack : public Powerup
{
public:
    HealthPack(Vector position);
    ~HealthPack();

    void applyEffect(std::shared_ptr<Player> player) override;

protected:
    void createVisuals() override;

private:
    float healing = 30.0f;
};