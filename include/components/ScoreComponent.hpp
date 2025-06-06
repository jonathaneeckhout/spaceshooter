#pragma once

#include <jengine/jengine.hpp>

class ScoreComponent : public Object
{
public:
    ScoreComponent();

    void setScore(unsigned int value);
    unsigned int getScore() { return score; };

    void addScore(unsigned int amount) { setScore(score + amount); };
    void removeScore(unsigned int amount) { setScore(score - amount); };

private:
    unsigned int score = 0;
};