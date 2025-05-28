#include "maps/Map.hpp"

#include "enemies/Astroid.hpp"
#include "enemies/Disc.hpp"

Map::Map()
{
    game = Game::getInstance();
    if (game == nullptr)
    {
        return;
    }
}

Map::~Map()
{
    while (!entityQueue.empty())
    {
        QueuedEntity *queuedEntity = entityQueue.front();
        entityQueue.pop();

        delete queuedEntity;
    }
}

void Map::init()
{
    loadEntities();

    registerInputs();

    loadEnityQueue();

    playBackgroundSound();
}

void Map::cleanup()
{
    deregisterInputs();
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
    Controls *controls = Controls::getInstance();
    if (controls == nullptr)
    {
        return;
    }

    quitCallbackID = controls->addKeyHandler([this](std::string key, bool pressed)
                                             {
        if (!pressed) {
            return;
        }

        if(Controls::getInstance()->isMapping("Quit", key)) {
            game->stop();
        } });
}

void Map::deregisterInputs()
{
    Controls *controls = Controls::getInstance();
    if (controls == nullptr)
    {
        return;
    }

    controls->removeKeyHandler(quitCallbackID);
}

bool Map::addProjectile(std::shared_ptr<Entity> projectile)
{
    return projectiles->addChild(projectile);
}

bool Map::addPowerup(std::shared_ptr<Entity> projectile)
{
    return powerups->addChild(projectile);
}

void Map::loadEnityQueue() {}

void Map::playBackgroundSound() {}

void Map::pushEntityToQueue(float loadTime, std::vector<std::shared_ptr<Entity>> entity)
{
    QueuedEntity *queuedEntity = new QueuedEntity();
    queuedEntity->loadTime = loadTime;
    queuedEntity->entities = entity;
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

std::weak_ptr<Player> Map::getPlayer()
{
    return player;
}