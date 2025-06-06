#pragma once

#include <jengine/jengine.hpp>
#include <string>
#include "components/ScoreComponent.hpp"

class ScoreDisplayComponent : public Object
{
public:
    ScoreDisplayComponent(Vector position, ScoreComponent *score, unsigned int size, const std::string &resourceName);

private:
    ScoreComponent *score = nullptr;

    TextComponent *label = nullptr;

    void onScoreChanged(unsigned int value);
};
