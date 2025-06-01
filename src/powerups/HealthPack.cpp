#include "powerups/HealthPack.hpp"

HealthPack::HealthPack(Vector position) : Powerup(position) {}

HealthPack::~HealthPack() {}

void HealthPack::createVisuals()
{
    auto body = Game::create<Square>(Vector{-8, -8}, Vector(16.0, 16.0));

    body->setColor(0xCE, 0x11, 0x27, 255);

    addChild(body);
}

void HealthPack::applyEffect(Player* player)
{
    player->heal(healing);
}
