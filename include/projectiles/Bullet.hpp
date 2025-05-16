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

    void init() override;

    void update(float dt) override;

private:
    float destroyTime = 2.0;

    std::shared_ptr<Timer> destroyTimer = nullptr;

    void createVisuals();

    void destroyCallback();

    void handleCollisiontStarted(std::weak_ptr<CollisionShape> shape);
    void handleCollisiontEnded(std::weak_ptr<CollisionShape> shape);
};