#include "SpaceShooter.hpp"

#include "enemies/Astroid.hpp"
#include "enemies/Dummy.hpp"

#include <iostream>

SpaceShooter::SpaceShooter()
{
    Renderer *renderer = Renderer::getInstance();
    if (renderer == nullptr)
    {
        return;
    }

    renderer->setWindowTitle("SpaceShooter");

    game = Game::getInstance();
    if (game == nullptr)
    {
        return;
    }
}

SpaceShooter::~SpaceShooter()
{
    while (!entityQueue.empty())
    {
        QueuedEntity *queuedEntity = entityQueue.front();
        entityQueue.pop();

        delete queuedEntity;
    }
}

void SpaceShooter::init()
{
    loadEntities();

    registerInputs();

    loadEnityQueue();
}

void SpaceShooter::loadEntities()
{
    entities = Game::create<Entity>();
    entities->setName("Entities");
    addChild(entities);

    projectiles = Game::create<Entity>();
    projectiles->setName("Projectiles");
    entities->addChild(projectiles);

    player = Game::create<Player>(Vector(400.0, 520.0));
    player->setName("Player");
    player->spaceShooter = this;
    entities->addChild(player);

    queueTimer = Game::create<Timer>(0.0);
    queueTimer->setName("QueueTimer");
    queueTimer->setCallback([this](void *)
                            { queueTimerCallback(); });
    addChild(queueTimer);
}

void SpaceShooter::update(float)
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

void SpaceShooter::registerInputs()
{
    Controls *controls = Controls::getInstance();
    if (controls == nullptr)
    {
        return;
    }

    controls->keyPressHandlers.push_back([this](std::string key)
                                         { 
        if(key == "Escape") {
            game->stop();
        } });
}

bool SpaceShooter::addProjectile(std::shared_ptr<Entity> projectile)
{
    return projectiles->addChild(projectile);
}

void SpaceShooter::loadEnityQueue()
{
    pushEntityToQueue(1.0, Game::create<Astroid>(Vector(400, 0)));
    pushEntityToQueue(1.0, Game::create<Astroid>(Vector(300, 0)));
    pushEntityToQueue(1.0, Game::create<Astroid>(Vector(200, 0)));
    pushEntityToQueue(1.0, Game::create<Astroid>(Vector(100, 0)));

    pushEntityToQueue(1.0, Game::create<Astroid>(Vector(400, 0)));
    pushEntityToQueue(1.0, Game::create<Astroid>(Vector(500, 0)));
    pushEntityToQueue(1.0, Game::create<Astroid>(Vector(600, 0)));
    pushEntityToQueue(1.0, Game::create<Astroid>(Vector(700, 0)));
}

void SpaceShooter::pushEntityToQueue(float loadTime, std::shared_ptr<Entity> entity)
{
    QueuedEntity *queuedEntity = new QueuedEntity();
    queuedEntity->loadTime = loadTime;
    queuedEntity->entity = entity;
    entityQueue.push(queuedEntity);
}

void SpaceShooter::queueTimerCallback()
{
    QueuedEntity *queuedEntity = entityQueue.front();
    entities->addChild(queuedEntity->entity);

    entityQueue.pop();

    delete queuedEntity;
}