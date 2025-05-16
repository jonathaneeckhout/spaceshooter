#include "enemies/Enemy.hpp"

Enemy::Enemy(Vector position) : Body(position) {}

Enemy::Enemy(Vector position, Vector velocity) : Body(position, velocity) {}

Enemy::~Enemy() {}

void Enemy::hurt(float amount)
{
    health -= amount;

    if (health <= 0.0)
    {
        health = 0.0;

        queueDelete();
    }
}