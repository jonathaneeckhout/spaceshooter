#pragma once

#include <jengine/jengine.hpp>

class GameEndComponent : public Object
{
public:
    GameEndComponent(Object *player, Object *lastEnemy, float timeout);
    ~GameEndComponent();

private:
    Object *player = nullptr;
    TimerComponent *timeoutTimer = nullptr;
    bool done = false;
    bool won = false;
    unsigned int score = 0;

    void onPlayerDied();
    void onLastEnemyDied();
    void triggerCallback();
};