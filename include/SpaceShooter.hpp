#pragma once

#include <queue>

#include <jengine/jengine.hpp>
#include "Player.hpp"

class QueuedEntity
{
public:
    float loadTime = 0;
    Entity *entity = nullptr;
};

class SpaceShooter : public Object
{
public:
    SpaceShooter();
    ~SpaceShooter();

    void update(float dt) override;

    bool addProjectile(Entity *projectile);

private:
    Game *game = nullptr;
    Player *player = nullptr;

    Entity *entities = nullptr;
    Entity *projectiles = nullptr;

    Timer *queueTimer = nullptr;
    std::queue<QueuedEntity *> entityQueue;

    void loadEntities();
    void registerInputs();
    void loadEnityQueue();
    void pushEntityToQueue(float loadTime, Entity *entity);
    void queueTimerCallback();
};