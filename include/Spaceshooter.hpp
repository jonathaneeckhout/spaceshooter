#pragma once

#include <jengine/jengine.hpp>

class Spaceshooter
{
public:
    ~Spaceshooter();

    Spaceshooter(const Spaceshooter &) = delete;

    static Spaceshooter *getInstance();
    static void deleteInstance();

    void setPlayer(Object *newPlayer) { player = newPlayer; };
    Object *getPlayer() { return player; };

    void setMap(Object *newMap) { map = newMap; };
    Object *getMap() { return map; };

    Vector directionToPlayer(Vector position);

private:
    static Spaceshooter *instancePtr;

    Object *player = nullptr;
    Object *map = nullptr;

    Spaceshooter();
};