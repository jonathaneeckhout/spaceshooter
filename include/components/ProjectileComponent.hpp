#pragma once

#include <jengine/jengine.hpp>

class ProjectileComponent : public Component
{
public:
    ProjectileComponent(TransformComponent *transform, float speed, float damage);

    void update(float dt) override;

private:
    TransformComponent *transform = nullptr;

    float speed = 1200.0;
    float damage = 10.0;
};
