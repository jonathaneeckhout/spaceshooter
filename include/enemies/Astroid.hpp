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
    void loadEntities();

    void createVisuals();
};