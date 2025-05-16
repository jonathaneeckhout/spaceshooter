#pragma once

#include <jengine/jengine.hpp>

#include "enemies/Enemy.hpp"

class Astroid : public Enemy
{
public:
    Astroid(Vector position);
    ~Astroid();

    void init() override;

    void update(float dt) override;

private:
    float destroyTime = 5.0;

    std::shared_ptr<Timer> destroyTimer;

    void loadEntities();

    void createVisuals();

    void destroyCallback();
};