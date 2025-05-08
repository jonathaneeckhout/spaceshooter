#pragma once

#include <jengine/jengine.hpp>

class Enemy : public Entity
{
public:
    float speed = 0.0;
    float health = 100.0;

    CollisionShape *collisionShape = nullptr;

    Enemy(Vector position);
    Enemy(Vector position, Vector velocity);
    ~Enemy();
};