#pragma once

#include <queue>

#include <jengine/jengine.hpp>

class QueuedObjects
{
public:
    float loadTime = 0;
    std::vector<Object *> objects;
};

class ObjectQueueComponent : public Object
{

public:
    ObjectQueueComponent(Object *spawnLocation);
    ~ObjectQueueComponent();

    void pushEntityToQueue(float loadTime, std::vector<Object *> objects);

    void stop();

private:
    Object *spawnLocation = nullptr;
    std::queue<QueuedObjects *> objectQueue;

    TimerComponent *queueTimer = nullptr;

    void startIfNotEmpty();
    void queueTimerCallback();
};