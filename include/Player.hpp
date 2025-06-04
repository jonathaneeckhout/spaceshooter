#pragma once

#include <string>

#include <jengine/jengine.hpp>
namespace spaceshooter
{
    namespace player
    {
        Object *createPlayer(std::string name, Object *map, Vector position);
    }
}
