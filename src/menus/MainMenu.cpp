#include <algorithm>

#include "menus/MainMenu.hpp"

MainMenu::MainMenu() {}

MainMenu::~MainMenu() {}

void MainMenu::init()
{
    registerInputs();

    createVisuals();

    selectNextButton(0);
}

void MainMenu::registerInputs()
{
    Controls *controls = Controls::getInstance();
    if (controls == nullptr)
    {
        return;
    }

    controls->keyPressHandlers.push_back([this](const std::string &key)
                                         { handleKeyPress(key); });
}

void MainMenu::handleKeyPress(const std::string &key)
{
    auto controls = Controls::getInstance();

    if (controls->isMapping("Quit", key))
    {
        Game::getInstance()->stop();
    }
    else if (controls->isMapping("MoveUp", key))
    {
        selectNextButton(-1);
    }
    else if (controls->isMapping("MoveDown", key))
    {
        selectNextButton(1);
    }
}

void MainMenu::createVisuals()
{
    buttonPanel = Game::create<Square>(Vector(250, 200), Vector(300, 256));
    buttonPanel->setColor(255, 0, 0, 255);
    addChild(buttonPanel);

    playButton = Game::create<Button>(Vector(16, 16), Vector(300 - 32, 64));
    playButton->setColor(32, 32, 32, 255);
    buttonPanel->addChild(playButton);

    settingsButton = Game::create<Button>(Vector(16, 16 + (16 + 64)), Vector(300 - 32, 64));
    settingsButton->setColor(32, 32, 32, 255);
    buttonPanel->addChild(settingsButton);

    quitButton = Game::create<Button>(Vector(16, 16 + 2 * (16 + 64)), Vector(300 - 32, 64));
    quitButton->setColor(32, 32, 32, 255);
    buttonPanel->addChild(quitButton);
}

void MainMenu::selectNextButton(int increment)
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
}