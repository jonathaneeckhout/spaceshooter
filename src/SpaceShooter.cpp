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

    loadEntities();

    registerInputs();

    loadEnityQueue();
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

void SpaceShooter::loadEntities()
{
    entities = new Entity();
    entities->name = "Entities";
    addChild(entities);

    projectiles = new Entity();
    projectiles->name = "Projectiles";
    entities->addChild(projectiles);

    player = new Player(Vector(400.0, 520.0));
    player->name = "Player";
    player->spaceShooter = this;
    entities->addChild(player);

    queueTimer = new Timer(0.0);
    queueTimer->name = "QueueTimer";
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

    std::cout << entities->getChildren().size() << std::endl;
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

bool SpaceShooter::addProjectile(Entity *projectile)
{
    return projectiles->addChild(projectile);
}

void SpaceShooter::loadEnityQueue()
{
    pushEntityToQueue(1.0, new Astroid(Vector(400, 0)));
    pushEntityToQueue(1.0, new Astroid(Vector(300, 0)));
    pushEntityToQueue(1.0, new Astroid(Vector(200, 0)));
    pushEntityToQueue(1.0, new Astroid(Vector(100, 0)));

    pushEntityToQueue(1.0, new Astroid(Vector(400, 0)));
    pushEntityToQueue(1.0, new Astroid(Vector(500, 0)));
    pushEntityToQueue(1.0, new Astroid(Vector(600, 0)));
    pushEntityToQueue(1.0, new Astroid(Vector(700, 0)));
}

void SpaceShooter::pushEntityToQueue(float loadTime, Entity *entity)
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