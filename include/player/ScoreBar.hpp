#pragma once

#include <jengine/jengine.hpp>

class ScoreBar : public Entity
{
public:
    ScoreBar(Vector position);
    ~ScoreBar();

    void init() override;

    void setScore(unsigned int value);

private:
    unsigned int score = 0;

    Text *scoreText = nullptr;

    void createVisuals();
};