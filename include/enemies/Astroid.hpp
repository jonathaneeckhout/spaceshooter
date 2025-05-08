#pragma once

#include <jengine/jengine.hpp>

#include "enemies/Enemy.hpp"

class Astroid : public Enemy
{
public:
    Astroid(Vector position);
    ~Astroid();

    void update(float dt) override;

private:
    float destroyTime = 5.0;

    Timer *destroyTimer = nullptr;

    void loadEntities();

    void createVisuals();

    void destroyCallback();
};