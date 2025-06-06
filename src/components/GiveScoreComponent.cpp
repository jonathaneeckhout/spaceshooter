#include <cassert>

#include "components/GiveScoreComponent.hpp"
#include "components/ScoreComponent.hpp"

GiveScoreComponent::GiveScoreComponent(
    HealthComponent *health,
    unsigned int score)
    : score(score)
{
    assert(health != nullptr && "Missing score component");

    std::function<void(Object *)> handler = [this](Object *source)
    {
        onDeath(source);
    };

    health->addEventHandler<Object *>("onDeath", handler);
}

void GiveScoreComponent::onDeath(Object *)
{
    // (this) GiveScoreComponent // (parent) Enemy // (parent) Entities // (parent) Map // (child) Player
    auto player = getParent()->getParent()->getParent()->getChildByName("Player");

    auto scoreComp = player->getChild<ScoreComponent>();
    if (scoreComp == nullptr)
    {
        return;
    }

    scoreComp->addScore(score);
}