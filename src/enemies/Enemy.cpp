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
