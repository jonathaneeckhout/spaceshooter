#include "components/ObjectQueueComponent.hpp"

ObjectQueueComponent::ObjectQueueComponent(Object *spawnLocation) : spawnLocation(spawnLocation)
{
    queueTimer = new TimerComponent();

    std::function<void()> handler = [this]()
    {
        queueTimerCallback();
    };

    queueTimer->addEventHandler("onTimeout", handler);

    addChild(queueTimer);
}

ObjectQueueComponent::~ObjectQueueComponent()
{
    while (!objectQueue.empty())
    {
        QueuedObjects *queuedObjects = objectQueue.front();
        objectQueue.pop();

        for (auto object : queuedObjects->objects)
        {
            delete object;
        }

        delete queuedObjects;
    }
}

void ObjectQueueComponent::pushEntityToQueue(float loadTime, std::vector<Object *> objects)
{
    QueuedObjects *queuedObjects = new QueuedObjects();
    queuedObjects->loadTime = loadTime;
    queuedObjects->objects = objects;
    objectQueue.push(queuedObjects);

    startIfNotEmpty();
}

void ObjectQueueComponent::startIfNotEmpty()
{
    if (objectQueue.empty())
    {
        return;
    }

    QueuedObjects *queuedObjects = objectQueue.front();

    queueTimer->setTimeout(queuedObjects->loadTime);

    queueTimer->start();
}

void ObjectQueueComponent::queueTimerCallback()
{
    QueuedObjects *queuedObjects = objectQueue.front();
    for (auto object : queuedObjects->objects)
    {
        spawnLocation->addChild(object);
    }

    objectQueue.pop();

    delete queuedObjects;

    startIfNotEmpty();
}
