#pragma once

#include <jengine/jengine.hpp>
namespace spaceshooter
{
    namespace enemies
    {
        Object *createAstroid(Vector position);

        Object *createProbe(Vector position);

        Object *createDisc(Vector position);
    }
}
