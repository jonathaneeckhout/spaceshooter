#include "maps/Map.hpp"

#include "enemies/Astroid.hpp"
#include "enemies/Disc.hpp"

Map::Map() {}

Map::~Map() {}

void Map::init()
{
    game = Game::getInstance();
    if (game == nullptr)
    {
        return;
    }
    loadEntities();

    registerInputs();

    loadEnityQueue();

    playBackgroundSound();
}

void Map::cleanup()
{

    deregisterInputs();

    while (!entityQueue.empty())
    {
        QueuedEntity *queuedEntity = entityQueue.front();
        entityQueue.pop();

        for (auto entity : queuedEntity->entities)
        {
            delete entity;
        }

        delete queuedEntity;
    }
}

void Map::loadEntities()
{
    entities = Game::create<Entity>();
    entities->setName("Entities");
    addChild(entities);

    projectiles = Game::create<Entity>();
    projectiles->setName("Projectiles");
    entities->addChild(projectiles);

    powerups = Game::create<Entity>();
    powerups->setName("Powerups");
    entities->addChild(powerups);

    player = Game::create<Player>(Vector(400.0, 520.0));
    player->setName("Player");
    player->map = this;
    entities->addChild(player);

    queueTimer = Game::create<Timer>(0.0);
    queueTimer->setName("QueueTimer");
    queueTimer->setCallback([this](void *)
                            { queueTimerCallback(); });
    addChild(queueTimer);
}

void Map::update(float)
{
    if (!queueTimer->isRunning())
    {
        if (entityQueue.empty())
        {
            return;
        }

        QueuedEntity *queuedEntity = entityQueue.front();

        queueTimer->timeout = queuedEntity->loadTime;

        queueTimer->start();
    }
}

void Map::registerInputs()
{
    quitCallbackID = Game::getInstance()->controls->addKeyHandler([this](std::string key, bool pressed)
                                                                  {
        if (!pressed) {
            return;
        }

        if(Game::getInstance()->controls->isMapping("Quit", key)) {
            game->stop();
        } });
}

void Map::deregisterInputs()
{
    Game::getInstance()->controls->removeKeyHandler(quitCallbackID);
}

bool Map::addProjectile(Entity *projectile)
{
    return projectiles->addChild(projectile);
}

bool Map::addPowerup(Entity *projectile)
{
    return powerups->addChild(projectile);
}

void Map::pushEntityToQueue(float loadTime, std::vector<Entity *> entities)
{
    QueuedEntity *queuedEntity = new QueuedEntity();
    queuedEntity->loadTime = loadTime;
    queuedEntity->entities = entities;
    entityQueue.push(queuedEntity);
}

void Map::queueTimerCallback()
{
    QueuedEntity *queuedEntity = entityQueue.front();
    for (auto entity : queuedEntity->entities)
    {
        entities->addChild(entity);
    }

    entityQueue.pop();

    delete queuedEntity;
}

Player *Map::getPlayer()
{
    return player;
}
