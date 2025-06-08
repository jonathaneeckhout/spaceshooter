#include <format>

#include "components/FPSDisplay.hpp"

FPSDisplay::FPSDisplay(Vector position, unsigned int size, const std::string &resourceName)
{
    label = new TextComponent(position, "0 FPS", size, resourceName);
    addChild(label);
}

void FPSDisplay::update(float)
{
    label->setText(std::format("{} FPS", static_cast<int>(Game::getInstance()->getFPS())));
}