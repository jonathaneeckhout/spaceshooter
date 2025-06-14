#include "components/ButtonKeyboardComponent.hpp"

ButtonKeyboardComponent::ButtonKeyboardComponent()
{
    keyHandlerID = Game::getInstance()->controls->addKeyHandler([this](const std::string &key, bool pressed)
                                                                { handleKey(key, pressed); });
}

ButtonKeyboardComponent::~ButtonKeyboardComponent()
{
    Game::getInstance()->controls->removeKeyHandler(keyHandlerID);
}

void ButtonKeyboardComponent::addButton(Object *button)
{
    if (button == nullptr)
    {
        return;
    }

    buttons.push_back(button);

    selectNextButton(0, false);
}

void ButtonKeyboardComponent::handleKey(const std::string &key, bool pressed)
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

void ButtonKeyboardComponent::selectNextButton(int increment, bool playSound)
{
    auto prevButton = buttons[buttonOffset]->getChild<ButtonComponent>();
    if (prevButton)
    {
        prevButton->setIdle();
    }

    buttonOffset += increment;

    buttonOffset = std::clamp<int>(buttonOffset, 0, buttons.size() - 1);

    auto nextButton = buttons[buttonOffset]->getChild<ButtonComponent>();
    if (nextButton)
    {
        nextButton->setSelected();
    }

    if (playSound && prevButton != nextButton)
    {
        Game::getInstance()->mixer->playSound("button0");
    }
}

void ButtonKeyboardComponent::pressSelectedButton()
{
    auto selectedButton = buttons[buttonOffset]->getChild<ButtonComponent>();
    if (selectedButton)
    {
        selectedButton->setPressed();
    }
}
