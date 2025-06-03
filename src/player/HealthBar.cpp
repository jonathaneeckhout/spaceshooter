#include "player/HealthBar.hpp"

HealthBar::HealthBar(Vector position, float health, float maxHealth) : Entity(position), health(health), maxHealth(maxHealth) {}

HealthBar::~HealthBar() {}

void HealthBar::init()
{
    createVisuals();
}

void HealthBar::createVisuals()
{
    backgroundBar = Game::create<Square>(Vector(), Vector(128.0, 32.0));
    backgroundBar->setColor(0x36, 0x45, 0x4F, 0x88);
    addChild(backgroundBar);

    bar = Game::create<Square>(Vector(2.0, 2.0), Vector(124.0, 28.0));
    bar->setColor(0x25, 0xff, 0x22, 0xFF);
    addChild(bar);
}

void HealthBar::output() {}

void HealthBar::setHealth(float value)
{
    if (value < 0.0)
    {
        return;
    }

    if (value > maxHealth)
    {
        return;
    }

    health = value;

    bar->size.x = width * (health / maxHealth);
}
