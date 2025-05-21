#pragma once

#include <queue>

#include <jengine/jengine.hpp>
#include "maps/Map.hpp"
#include "player/Player.hpp"

class AstroidField : public Map
{
public:
    AstroidField();
    ~AstroidField();

protected:
    void loadEnityQueue() override;
};