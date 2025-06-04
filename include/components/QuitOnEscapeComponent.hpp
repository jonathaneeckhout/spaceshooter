#pragma once

#include <jengine/jengine.hpp>

class QuitOnEscapeComponent : public Component
{
public:
    QuitOnEscapeComponent();
    ~QuitOnEscapeComponent();

private:
    int quitCallbackID = 0;
};