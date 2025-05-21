#include "powerups/HealthPack.hpp"

HealthPack::HealthPack(Vector position) : Powerup(position) {}

HealthPack::~HealthPack() {}

void HealthPack::createVisuals()
{
    auto body = Game::create<Square>(Vector{-8, -8}, 16, 16);

    body->color = {0xCE, 0x11, 0x27, 255};

    addChild(body);
}

void HealthPack::applyEffect(std::shared_ptr<Player> player)
{
    player->heal(healing);
}
