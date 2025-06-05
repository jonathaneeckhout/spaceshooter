#pragma once

#include <jengine/jengine.hpp>

namespace spaceshooter
{
    namespace projectiles
    {
        Object *createBullet(Vector position, Vector direction, bool isPlayer);
    }
}