#pragma once

#include <jengine/jengine.hpp>

class ProjectileComponent : public Object
{
public:
    ProjectileComponent(TransformComponent *transform, CollisionComponent *collision, float speed, float damage);

    void update(float dt) override;

private:
    TransformComponent *transform = nullptr;

    float speed = 1200.0;
    float damage = 10.0;

    void onCollision(Object *object, bool collides);
};
