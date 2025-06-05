#include "components/QuitOnEscapeComponent.hpp"

QuitOnEscapeComponent::QuitOnEscapeComponent()
{
    quitCallbackID = Game::getInstance()->controls->addKeyHandler([](std::string key, bool pressed)
                                                                  {
        if (!pressed) {
            return;
        }

        if(Game::getInstance()->controls->isMapping("Quit", key)) {
            Game::getInstance()->stop();
        } });
}

QuitOnEscapeComponent::~QuitOnEscapeComponent()
{
    Game::getInstance()->controls->removeKeyHandler(quitCallbackID);
}
