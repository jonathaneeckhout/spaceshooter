#include <algorithm>

#include "menus/MainMenu.hpp"
#include "maps/AstroidField.hpp"

MainMenu::MainMenu() {}

MainMenu::~MainMenu() {}

void MainMenu::init()
{
    registerInputs();

    createVisuals();

    selectNextButton(0, false);

    Mixer::getInstance()->playSound("backgroundDeepSpaceAtmosphere");
}

void MainMenu::cleanup()
{
    deregisterInputs();

    // Mixer::getInstance()->stopAllSounds();

    Mixer::getInstance()->stopSound("backgroundDeepSpaceAtmosphere");
}

void MainMenu::registerInputs()
{
    Controls *controls = Controls::getInstance();
    if (controls == nullptr)
    {
        return;
    }

    keyHandlerID = controls->addKeyHandler([this](const std::string &key, bool pressed)
                                           { handleKey(key, pressed); });
}

void MainMenu::deregisterInputs()
{
    Controls *controls = Controls::getInstance();
    if (controls == nullptr)
    {
        return;
    }

    controls->removeKeyHandler(keyHandlerID);
}

void MainMenu::handleKey(const std::string &key, bool pressed)
{
    auto controls = Controls::getInstance();

    if (pressed && controls->isMapping("Quit", key))
    {
        Game::getInstance()->stop();
    }
    else if (pressed && controls->isMapping("MoveUp", key))
    {
        selectNextButton(-1, true);
    }
    else if (pressed && controls->isMapping("MoveDown", key))
    {
        selectNextButton(1, true);
    }
    else if (controls->isMapping("Enter", key))
    {
        if (pressed)
        {
            pressSelectedButton();
        }
        else
        {
            selectNextButton(0, false);
        }
    }
}

void MainMenu::createVisuals()
{
    buttonPanel = Game::create<Square>(Vector(250, 200), Vector(300, 256));
    buttonPanel->setColor(255, 0, 0, 255);
    addChild(buttonPanel);

    playButton = Game::create<Button>(Vector(16, 16), Vector(300 - 32, 64));
    playButton->setColor(32, 32, 32, 255);

    playButton->pressHandlers.push_back([this]()
                                        { handlePlay(); });

    buttonPanel->addChild(playButton);

    settingsButton = Game::create<Button>(Vector(16, 16 + (16 + 64)), Vector(300 - 32, 64));
    settingsButton->setColor(32, 32, 32, 255);

    settingsButton->pressHandlers.push_back([this]()
                                            { handleSettings(); });

    buttonPanel->addChild(settingsButton);

    quitButton = Game::create<Button>(Vector(16, 16 + 2 * (16 + 64)), Vector(300 - 32, 64));
    quitButton->setColor(32, 32, 32, 255);

    quitButton->pressHandlers.push_back([this]()
                                        { handleQuit(); });

    buttonPanel->addChild(quitButton);
}

void MainMenu::selectNextButton(int increment, bool playSound)
{
    auto prevButton = Game::safeCast<Button>(buttonPanel->getChild(buttonOffset));
    if (prevButton)
    {
        prevButton->setIdle();
    }

    buttonOffset += increment;

    buttonOffset = std::clamp<int>(buttonOffset, 0, buttonPanel->getChildrenSize() - 1);

    auto nextButton = Game::safeCast<Button>(buttonPanel->getChild(buttonOffset));
    if (nextButton)
    {
        nextButton->setSelected();
    }

    if (playSound && prevButton != nextButton)
    {
        Mixer::getInstance()->playSound("button0");
    }
}

void MainMenu::pressSelectedButton()
{
    auto selectedButton = Game::safeCast<Button>(buttonPanel->getChild(buttonOffset));
    if (selectedButton)
    {
        selectedButton->setPressed();
    }
}

void MainMenu::handlePlay()
{
    auto map = Game::create<AstroidField>();
    Game::getInstance()->setRootObject(map);
}

void MainMenu::handleSettings()
{
}

void MainMenu::handleQuit()
{
    Game::getInstance()->stop();
}