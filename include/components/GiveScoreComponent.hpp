#pragma once

#include <jengine/jengine.hpp>
#include "components/HealthComponent.hpp"

class GiveScoreComponent : public Object
{
public:
    GiveScoreComponent(HealthComponent *health, unsigned int score);

private:
    unsigned int score = 0;

    void onDeath(Object *source);
};