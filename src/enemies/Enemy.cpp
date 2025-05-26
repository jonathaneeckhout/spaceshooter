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

        Mixer::getInstance()->playSound("EnemyDestroyedExplosion");

        queueDelete();
    }
}

std::shared_ptr<Map> Enemy::getMap()
{
    auto entity = Game::safeCast<Entity>(parent);
    if (!entity)
    {
        return nullptr;
    }

    return Game::safeCast<Map>(entity->getParent());
}

std::shared_ptr<Player> Enemy::getPlayer()
{
    auto entity = Game::safeCast<Entity>(parent);
    if (!entity)
    {
        return nullptr;
    }

    auto map = Game::safeCast<Map>(entity->getParent());

    return Game::safeCast<Player>(map->getPlayer());
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

    const float leftBound = -64.0f;
    const float rightBound = 800.0f + 64.0f;
    const float topBound = -64.0f;
    const float bottomBound = 600.0f + 64.0f;

    if (pos.x < leftBound || pos.x > rightBound || pos.y < topBound || pos.y > bottomBound)
    {
        queueDelete();
        return true;
    }

    return false;
}