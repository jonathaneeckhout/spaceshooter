#pragma once

#include <jengine/jengine.hpp>

class FPSDisplay : public Object
{

public:
    FPSDisplay(Vector position, unsigned int size, const std::string &resourceName);

    void update(float dt) override;

private:
    TextComponent *label = nullptr;
};
