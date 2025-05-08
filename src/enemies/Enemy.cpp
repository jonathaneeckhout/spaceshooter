#include "enemies/Enemy.hpp"

Enemy::Enemy(Vector position) : Entity(position) {}

Enemy::Enemy(Vector position, Vector velocity) : Entity(position, velocity) {}

Enemy::~Enemy() {}