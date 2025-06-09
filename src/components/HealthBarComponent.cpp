#include <cassert>

#include "components/HealthBarComponent.hpp"

HealthBarComponent::HealthBarComponent(
    Vector position,
    HealthComponent *health,
    Vector size)
    : health(health),
      size(size)
{
    assert(health != nullptr && "Missing health component");

    backgroundBar = new SquareComponent(position, size, backgroundBarColor);
    addChild(backgroundBar);

    bar = new SquareComponent(position, size, barColor);
    addChild(bar);

    std::function<void(float)> handler = [this](float value)
    {
        onHealthChanged(value);
    };

    health->addEventHandler<float>("onChanged", handler);
}

void HealthBarComponent::setbackgroundBarColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    backgroundBarColor = {r, g, b, a};

    backgroundBar->setColor(r, g, b, a);
}
void HealthBarComponent::setBarColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    barColor = {r, g, b, a};

    bar->setColor(r, g, b, a);
}

void HealthBarComponent::onHealthChanged(float)
{
    bar->setSize(
        Vector(size.x * (health->getHealth() / health->getMaxHealth()),
               size.y));
}
