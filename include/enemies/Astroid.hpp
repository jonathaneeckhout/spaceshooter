#pragma once

#include <jengine/jengine.hpp>

#include "enemies/Enemy.hpp"

class Astroid : public Enemy
{
public:
    Astroid(Vector position);
    ~Astroid();

    void init() override;
    void cleanup() override;

    void update(float dt) override;

protected:
    void dropLoot() override;

private:
    float collisionDamage = 30.0;

    void loadEntities();

    void createVisuals();

    void handleCollisiontStarted(CollisionShape *shape);
};