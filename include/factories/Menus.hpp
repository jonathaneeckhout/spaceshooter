#pragma once

#include <jengine/jengine.hpp>

namespace spaceshooter
{
    namespace menus
    {
        Object *createMainMenu();
        Object *createGameEndedMenu(bool won, unsigned int score);
    }
}
