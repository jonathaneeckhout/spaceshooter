#include "components/PlayerInputComponent.hpp"

PlayerInputComponent::PlayerInputComponent()
{
    keyHandlerID = Game::getInstance()->controls->addKeyHandler([this](const std::string &key, bool pressed)
                                                                { handleKey(key, pressed); });
}

PlayerInputComponent::~PlayerInputComponent()
{
    Game::getInstance()->controls->removeKeyHandler(keyHandlerID);
}

void PlayerInputComponent::handleKey(const std::string &key, bool press)
{
    auto controls = Game::getInstance()->controls;

    if (controls->isMapping("MoveLeft", key))
    {
        moveLeft = press;
    }
    else if (controls->isMapping("MoveRight", key))
    {
        moveRight = press;
    }
    else if (controls->isMapping("MoveUp", key))
    {
        moveUp = press;
    }
    else if (controls->isMapping("MoveDown", key))
    {
        moveDown = press;
    }
    else if (controls->isMapping("Shoot", key))
    {
        shoot = press;
    }
}