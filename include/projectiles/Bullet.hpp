#pragma once

#include <string>
#include <jengine/jengine.hpp>

class Bullet : public Entity
{
public:
    float speed = 600.0;
    float damage = 10.0;

    Bullet(Vector position, Vector direction);
    ~Bullet();

    void update(float dt) override;

private:
    float destroyTime = 2.0;

    Timer *destroyTimer = nullptr;

    void createVisuals();

    void destroyCallback();

    void handleCollisiontStarted(CollisionShape *shape);
    void handleCollisiontEnded(CollisionShape *shape);
};