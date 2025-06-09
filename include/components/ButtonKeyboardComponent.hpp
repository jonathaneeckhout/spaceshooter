#pragma once

#include <vector>

#include <jengine/jengine.hpp>

class ButtonKeyboardComponent : public Object
{

public:
private:
    int buttonOffset = 0;
    std::vector<Object *> buttons;
};