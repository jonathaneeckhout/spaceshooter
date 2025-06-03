#pragma once

#include <jengine/jengine.hpp>

class Zap : public Entity
{
public:
    float speed = 300.0;
    float damage = 10.0;

    Zap(Vector position, Vector direction);
    ~Zap();

    void init() override;

    void update(float dt) override;

private:
    float destroyTime = 4.0;

    Timer *destroyTimer = nullptr;

    void createVisuals();

    void destroyCallback();

    void handleCollisiontStarted(CollisionShape *shape);
};
