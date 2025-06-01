#pragma once

#include <jengine/jengine.hpp>
#include "player/Player.hpp"
#include "maps/Map.hpp"

class Enemy : public Body
{
public:
    float speed = 0.0;
    float health = 100.0;
    unsigned int score = 0;

    Enemy(Vector position);
    Enemy(Vector position, Vector velocity);
    ~Enemy();

    void hurt(float amount);

protected:
    Map *getMap();
    Player *getPlayer();

    bool deleteOffscreen();

    void giveScore();

    virtual void dropLoot();
};