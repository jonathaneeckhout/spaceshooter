#pragma once

#include <string>

#include <jengine/jengine.hpp>

class PlayerInputComponent : public Object
{
public:
    bool moveLeft = false;
    bool moveRight = false;
    bool moveUp = false;
    bool moveDown = false;

    bool shoot = false;

    PlayerInputComponent();
    ~PlayerInputComponent();

private:
    int keyHandlerID = 0;

    void handleKey(const std::string &key, bool press);
};