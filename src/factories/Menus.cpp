#include <format>

#include "factories/Menus.hpp"
#include "factories/Maps.hpp"
#include "components/ButtonKeyboardComponent.hpp"

namespace spaceshooter
{
    namespace menus
    {
        Object *createMainMenu()
        {
            Object *obj = new Object();
            obj->setName("MainMenu");

            Vector windowSize = Game::getInstance()->renderer->getWindowSize();

            auto title = new TextComponent(Vector(windowSize.x / 2, 100), "Spaceshooter", 64, "defaultFont");
            title->centered = true;
            obj->addChild(title);

            auto buttonPanel = new SquareComponent(Vector(windowSize.x / 2 - 150, 200), Vector(300, 256), {255, 0, 0, 255});
            obj->addChild(buttonPanel);

            auto playButton = new TextButtonComponent(Vector(16, 16), Vector(300 - 32, 64), "Play", 32, "defaultFont");

            std::function<void()> playHandler = []()
            {
                auto map = spaceshooter::maps::createAstroidField();
                Game::getInstance()->setRootObject(map);
            };
            playButton->addEventHandler("onPressed", playHandler);

            buttonPanel->addChild(playButton);

            auto settingsButton = new TextButtonComponent(Vector(16, 16 + (16 + 64)), Vector(300 - 32, 64), "Settings", 32, "defaultFont");
            buttonPanel->addChild(settingsButton);

            auto quitButton = new TextButtonComponent(Vector(16, 16 + 2 * (16 + 64)), Vector(300 - 32, 64), "Quit", 32, "defaultFont");

            std::function<void()> quitHandler = []()
            {
                Game::getInstance()->stop();
            };
            quitButton->addEventHandler("onPressed", quitHandler);

            buttonPanel->addChild(quitButton);

            auto buttonControls = new ButtonKeyboardComponent();
            buttonControls->addButton(playButton);
            buttonControls->addButton(settingsButton);
            buttonControls->addButton(quitButton);

            buttonPanel->addChild(buttonControls);

            auto soundLoader = new SoundLoaderComponent();
            soundLoader->addSound("backgroundDeepSpaceAtmosphere", "backgroundDeepSpaceAtmosphere");
            soundLoader->addSound("button0", "button0");
            obj->addChild(soundLoader);

            Game::getInstance()->mixer->playSound("backgroundDeepSpaceAtmosphere");

            return obj;
        }

        Object *createGameEndedMenu(bool won, unsigned int score)
        {
            Object *obj = new Object();
            obj->setName("GameEndedMenu");

            Vector windowSize = Game::getInstance()->renderer->getWindowSize();

            auto title = new TextComponent(Vector(windowSize.x / 2, 100), won ? "You won!" : "You died!", 64, "defaultFont");
            title->centered = true;
            obj->addChild(title);

            auto buttonPanel = new SquareComponent(Vector(windowSize.x / 2 - 150, 200), Vector(300, 3 * 16 + 2 * 64), {255, 0, 0, 255});
            obj->addChild(buttonPanel);

            auto scoreLabel = new TextComponent(Vector(16, 16), std::format("Score: {}", score), 32, "defaultFont");
            buttonPanel->addChild(scoreLabel);

            auto continueButton = new TextButtonComponent(Vector(16, 16 * 2 + 32), Vector(300 - 32, 64), "Continue", 32, "defaultFont");

            std::function<void()> continueHandler = []()
            {
                auto mainMenu = createMainMenu();
                Game::getInstance()->setRootObject(mainMenu);
            };
            continueButton->addEventHandler("onPressed", continueHandler);

            buttonPanel->addChild(continueButton);

            auto buttonControls = new ButtonKeyboardComponent();
            buttonControls->addButton(continueButton);
            buttonPanel->addChild(buttonControls);

            return obj;
        }
    }
}
