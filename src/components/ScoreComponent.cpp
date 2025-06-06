#include "components/ScoreComponent.hpp"

ScoreComponent::ScoreComponent()
{
    events.createEvent<unsigned int>("onChanged");
}

void ScoreComponent::setScore(unsigned int value)
{
    unsigned int diff = value - score;

    score = value;

    events.trigger<unsigned int>("onChanged", diff);
}