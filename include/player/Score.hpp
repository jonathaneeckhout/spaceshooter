#pragma once

#include <jengine/jengine.hpp>

class Score : public Entity
{
public:
    Score(Vector position);
    ~Score();

    void init() override;

    void setScore(unsigned int value);

private:
    unsigned int score = 0;

    // std::shared_ptr<Label> scoreLabel;

    void createVisuals();
};