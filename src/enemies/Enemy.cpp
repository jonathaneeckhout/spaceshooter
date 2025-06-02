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

        giveScore();

        dropLoot();

        Game::getInstance()->mixer->playSound("EnemyDestroyedExplosion");

        queueDelete();
    }
}

Map *Enemy::getMap()
{
    auto entity = dynamic_cast<Entity *>(parent);
    if (!entity)
    {
        return nullptr;
    }

    return dynamic_cast<Map *>(entity->getParent());
}

Player *Enemy::getPlayer()
{
    auto entity = dynamic_cast<Entity *>(parent);
    if (!entity)
    {
        return nullptr;
    }

    auto map = dynamic_cast<Map *>(entity->getParent());
    if (!map)
    {
        return nullptr;
    }

    return map->getPlayer();
}

void Enemy::giveScore()
{
    auto player = getPlayer();
    if (player == nullptr)
    {
        return;
    }

    player->addScore(score);
}

void Enemy::dropLoot() {}

bool Enemy::deleteOffscreen()
{
    auto pos = getPosition();

    Vector windowSize = Game::getInstance()->renderer->getWindowSize();

    const float leftBound = -64.0f;
    const float rightBound = windowSize.x + 64.0f;
    const float topBound = -64.0f;
    const float bottomBound = windowSize.y + 64.0f;

    if (pos.x < leftBound || pos.x > rightBound || pos.y < topBound || pos.y > bottomBound)
    {
        queueDelete();
        return true;
    }

    return false;
}