#include "factories/Menus.hpp"

namespace spaceshooter
{
    namespace menus
    {
        Object *createMainMenu()
        {
            Object *obj = new Object();

            Vector windowSize = Game::getInstance()->renderer->getWindowSize();

            auto title = new TextComponent(Vector(windowSize.x / 2, 100), "Spaceshooter", 64, "defaultFont");
            title->centered = true;
            obj->addChild(title);

            auto buttonPanel = new SquareComponent(Vector(windowSize.x / 2 - 150, 200), Vector(300, 256), {255, 0, 0, 255});
            obj->addChild(buttonPanel);

            auto playButton = new TextButtonComponent(Vector(16, 16), Vector(300 - 32, 64), "Play", 32, "defaultFont");
            buttonPanel->addChild(playButton);

            auto settingsButton = new TextButtonComponent(Vector(16, 16 + (16 + 64)), Vector(300 - 32, 64), "Settings", 32, "defaultFont");
            buttonPanel->addChild(settingsButton);

            auto quitButton = new TextButtonComponent(Vector(16, 16 + 2 * (16 + 64)), Vector(300 - 32, 64), "Quit", 32, "defaultFont");
            buttonPanel->addChild(quitButton);

            return obj;
        }
    }
}
