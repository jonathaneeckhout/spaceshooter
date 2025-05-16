#pragma once

#include <queue>

#include <jengine/jengine.hpp>
#include "Player.hpp"

class QueuedEntity
{
public:
    float loadTime = 0;
    std::shared_ptr<Entity> entity = nullptr;
};

class SpaceShooter : public Object
{
public:
    SpaceShooter();
    ~SpaceShooter();

    void init() override;

    void update(float dt) override;

    bool addProjectile(std::shared_ptr<Entity> projectile);

private:
    Game *game = nullptr;
    std::shared_ptr<Player> player;

    std::shared_ptr<Entity> entities;
    std::shared_ptr<Entity> projectiles;

    std::shared_ptr<Timer> queueTimer;
    std::queue<QueuedEntity *> entityQueue;

    void loadEntities();
    void registerInputs();
    void loadEnityQueue();
    void pushEntityToQueue(float loadTime, std::shared_ptr<Entity> entity);
    void queueTimerCallback();
};