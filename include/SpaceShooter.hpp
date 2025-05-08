#pragma once

#include <jengine/jengine.hpp>
#include "Player.hpp"

class SpaceShooter : public Object
{
public:
    SpaceShooter();
    ~SpaceShooter();

    bool addProjectile(Entity *projectile);

private:
    Game *game = nullptr;
    Player *player = nullptr;

    Entity *entities = nullptr;
    Entity *projectiles = nullptr;

    void loadEntities();
    void registerInputs();
};