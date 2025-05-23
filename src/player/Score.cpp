#include "player/Score.hpp"

Score::Score(Vector position) : Entity(position) {}

Score::~Score() {}

void Score::init()
{
    createVisuals();
}

void Score::createVisuals()
{
    // TODO: figure out why this is crashing
    // scoreLabel = Game::create<Label>(Vector(), "Score:0000", "default", 32);
    // addChild(scoreLabel);

}

void Score::setScore(unsigned int value)
{
    // Todo: update visuals

    score = value;
}