#include <cassert>

#include "components/ScoreDisplayComponent.hpp"

ScoreDisplayComponent::ScoreDisplayComponent(
    Vector position,
    ScoreComponent *score,
    unsigned int size,
    const std::string &resourceName)
    : score(score)
{
    assert(score != nullptr && "Missing score component");

    TransformComponent *transform = new TransformComponent(position);
    addChild(transform);

    label = new TextComponent(transform, std::to_string(score->getScore()), size, resourceName);
    addChild(label);

    std::function<void(unsigned int)> handler = [this](unsigned int value)
    {
        onScoreChanged(value);
    };

    score->addEventHandler<unsigned int>("onChanged", handler);
}

void ScoreDisplayComponent::onScoreChanged(unsigned int)
{
    label->setText(std::to_string(score->getScore()));
}
