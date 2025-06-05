#pragma once

#include <jengine/jengine.hpp>

class QuitOnEscapeComponent : public Object
{
public:
    QuitOnEscapeComponent();
    ~QuitOnEscapeComponent();

private:
    int quitCallbackID = 0;
};