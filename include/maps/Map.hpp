#pragma once

#include <queue>

#include <jengine/jengine.hpp>
#include "player/Player.hpp"
#include "powerups/Powerup.hpp"

class QueuedEntity
{
public:
    float loadTime = 0;
    std::vector<Entity *> entities;
};

class Map : public Object
{
public:
    Map();
    ~Map();

    void init() override;
    void cleanup() override;

    void update(float dt) override;

    bool addProjectile(Entity *projectile);
    bool addPowerup(Entity *powerup);

    Player *getPlayer();

protected:
    Game *game = nullptr;
    Player *player = nullptr;

    Entity *entities = nullptr;
    Entity *projectiles = nullptr;
    Entity *powerups = nullptr;

    Timer *queueTimer = nullptr;
    std::queue<QueuedEntity *> entityQueue;

    int quitCallbackID = 0;

    void loadEntities();
    void registerInputs();
    void deregisterInputs();

    virtual void loadEnityQueue() {};
    virtual void playBackgroundSound() {};
    virtual void stopBackgroundSound() {};

    void pushEntityToQueue(float loadTime, std::vector<Entity *> entities);
    void queueTimerCallback();
};