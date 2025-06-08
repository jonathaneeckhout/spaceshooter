#pragma once

#include <jengine/jengine.hpp>

class LootBehaviorComponent : public Object
{
public:
    LootBehaviorComponent(TransformComponent *transform, CollisionComponent *collision, float healing, float speed = 100);

    void update(float dt) override;

private:
    TransformComponent *transform = nullptr;
    float healing = 0.0f;
    float speed = 100.0f;

    void onCollision(Object *object, bool collides);
};