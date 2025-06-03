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

    Game::getInstance()->mixer->playSound("backgroundDeepSpaceAtmosphere");
}

void MainMenu::cleanup()
{
    deregisterInputs();

    Game::getInstance()->mixer->stopSound("backgroundDeepSpaceAtmosphere");
}

void MainMenu::registerInputs()
{
    keyHandlerID = Game::getInstance()->controls->addKeyHandler([this](const std::string &key, bool pressed)
                                                                { handleKey(key, pressed); });
}

void MainMenu::deregisterInputs()
{
    Game::getInstance()->controls->removeKeyHandler(keyHandlerID);
}

void MainMenu::handleKey(const std::string &key, bool pressed)
{
    auto controls = Game::getInstance()->controls;

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
    Vector windowSize = Game::getInstance()->renderer->getWindowSize();

    title = Game::create<Text>(Vector(windowSize.x / 2, 100), "Spaceshooter", 64, "defaultFont");
    title->centered = true;
    addChild(title);

    buttonPanel = Game::create<Square>(Vector(windowSize.x / 2 - 150, 200), Vector(300, 256));
    buttonPanel->setColor(255, 0, 0, 255);
    addChild(buttonPanel);

    playButton = Game::create<TextButton>(Vector(16, 16), Vector(300 - 32, 64), "Play", 32, "defaultFont");
    playButton->setColor(32, 32, 32, 255);

    playButton->pressHandlers.push_back([this]()
                                        { handlePlay(); });

    buttonPanel->addChild(playButton);

    settingsButton = Game::create<TextButton>(Vector(16, 16 + (16 + 64)), Vector(300 - 32, 64), "Settings", 32, "defaultFont");
    settingsButton->setColor(32, 32, 32, 255);

    settingsButton->pressHandlers.push_back([this]()
                                            { handleSettings(); });

    buttonPanel->addChild(settingsButton);

    quitButton = Game::create<TextButton>(Vector(16, 16 + 2 * (16 + 64)), Vector(300 - 32, 64), "Quit", 32, "defaultFont");
    quitButton->setColor(32, 32, 32, 255);

    quitButton->pressHandlers.push_back([this]()
                                        { handleQuit(); });

    buttonPanel->addChild(quitButton);
}

void MainMenu::selectNextButton(int increment, bool playSound)
{
    auto prevButton = dynamic_cast<Button *>(buttonPanel->getChild(buttonOffset));
    if (prevButton)
    {
        prevButton->setIdle();
    }

    buttonOffset += increment;

    buttonOffset = std::clamp<int>(buttonOffset, 0, buttonPanel->getChildrenSize() - 1);

    auto nextButton = dynamic_cast<Button *>(buttonPanel->getChild(buttonOffset));
    if (nextButton)
    {
        nextButton->setSelected();
    }

    if (playSound && prevButton != nextButton)
    {
        Game::getInstance()->mixer->playSound("button0");
    }
}

void MainMenu::pressSelectedButton()
{
    auto selectedButton = dynamic_cast<Button *>(buttonPanel->getChild(buttonOffset));
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
