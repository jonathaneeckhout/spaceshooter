#pragma once

#include <vector>

#include <jengine/jengine.hpp>

class ButtonKeyboardComponent : public Object
{

public:
    ButtonKeyboardComponent();
    ~ButtonKeyboardComponent();

    void addButton(Object *button);

private:
    int keyHandlerID = 0;

    int buttonOffset = 0;
    std::vector<Object *> buttons;

    void handleKey(const std::string &key, bool press);
    void selectNextButton(int increment, bool playSound);
    void pressSelectedButton();
};