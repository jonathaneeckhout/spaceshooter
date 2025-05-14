#pragma once

#include <jengine/jengine.hpp>

#include "enemies/Enemy.hpp"

class Dummy : public Enemy
{
public:
    Dummy(Vector position);
    ~Dummy();

    void update(float dt) override;

private:
    void loadEntities();

    void createVisuals();
};