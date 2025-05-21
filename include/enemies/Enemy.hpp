#pragma once

#include <jengine/jengine.hpp>
#include "player/Player.hpp"
#include "maps/Map.hpp"

class Enemy : public Body
{
public:
    float speed = 0.0;
    float health = 100.0;

    Enemy(Vector position);
    Enemy(Vector position, Vector velocity);
    ~Enemy();

    void hurt(float amount);

protected:
    std::shared_ptr<Map> getMap();
    std::shared_ptr<Player> getPlayer();

    virtual void dropLoot();
};