#include "player/ScoreBar.hpp"
#include <string>

ScoreBar::ScoreBar(Vector position) : Entity(position) {}

ScoreBar::~ScoreBar() {}

void ScoreBar::init()
{
    createVisuals();
}

void ScoreBar::createVisuals()
{
    scoreText = Game::create<Text>(Vector(), "0", 32, "defaultFont");
    addChild(scoreText);
}

void ScoreBar::setScore(unsigned int value)
{
    score = value;

    scoreText->setText(std::to_string(score));
}