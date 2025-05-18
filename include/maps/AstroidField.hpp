#pragma once

#include <queue>

#include <jengine/jengine.hpp>
#include "maps/Map.hpp"
#include "Player.hpp"

class AstroidField : public Map
{
public:
    AstroidField();
    ~AstroidField();

protected:
    void loadEnityQueue() override;
};