#include "components/GameEndComponent.hpp"
#include "components/ScoreComponent.hpp"

GameEndComponent::GameEndComponent(Object *player, Object *lastEnemy, float timeout) : player(player)
{
    events.createEvent<bool, unsigned int>("onGameEnded");

    timeoutTimer = new TimerComponent(timeout, false);
    std::function<void()> timeoutHandler = [this]()
    {
        triggerCallback();
    };
    timeoutTimer->addEventHandler("onTimeout", timeoutHandler);
    addChild(timeoutTimer);

    std::function<void()> playerDiedHandler = [this]()
    {
        onPlayerDied();
    };
    player->addEventHandler("onDeleted", playerDiedHandler);

    std::function<void()> lastEnemyDiedHandler = [this]()
    {
        onLastEnemyDied();
    };
    lastEnemy->addEventHandler("onDeleted", lastEnemyDiedHandler);
}

GameEndComponent::~GameEndComponent()
{
    if (done)
    {
        return;
    }
    done = true;
    won = true;

    timeoutTimer->start();
}

void GameEndComponent::onPlayerDied()
{
    if (done)
    {
        return;
    }
    done = true;
    won = false;

    score = player->getChild<ScoreComponent>()->getScore();

    timeoutTimer->start();
}

void GameEndComponent::onLastEnemyDied()
{
    if (done)
    {
        return;
    }
    done = true;
    won = true;

    score = player->getChild<ScoreComponent>()->getScore();

    timeoutTimer->start();
}

void GameEndComponent::triggerCallback()
{
    events.trigger("onGameEnded", won, score);
}