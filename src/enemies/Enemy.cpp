#include "enemies/Enemy.hpp"

Enemy::Enemy(Vector position) : Entity(position) {}

Enemy::Enemy(Vector position, Vector velocity) : Entity(position, velocity) {}

Enemy::~Enemy() {}

void Enemy::hurt(float amount)
{
    health -= amount;

    if (health < 0.0)
    {
        health = 0.0;

        queueDelete();
    }
}