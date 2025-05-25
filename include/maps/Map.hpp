#pragma once

#include <queue>

#include <jengine/jengine.hpp>
#include "player/Player.hpp"
#include "powerups/Powerup.hpp"

class QueuedEntity
{
public:
    float loadTime = 0;
    std::vector<std::shared_ptr<Entity>> entities;
};

class Map : public Object
{
public:
    Map();
    ~Map();

    void init() override;

    void update(float dt) override;

    bool addProjectile(std::shared_ptr<Entity> projectile);
    bool addPowerup(std::shared_ptr<Entity> powerup);

    std::weak_ptr<Player> getPlayer();

protected:
    Game *game = nullptr;
    std::shared_ptr<Player> player;

    std::shared_ptr<Entity> entities;
    std::shared_ptr<Entity> projectiles;
    std::shared_ptr<Entity> powerups;

    std::shared_ptr<Timer> queueTimer;
    std::queue<QueuedEntity *> entityQueue;

    void loadEntities();
    void registerInputs();

    virtual void loadEnityQueue();
    virtual void playBackgroundSound();

    void pushEntityToQueue(float loadTime, std::vector<std::shared_ptr<Entity>> entity);
    void queueTimerCallback();
};