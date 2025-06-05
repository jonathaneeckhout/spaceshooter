#pragma once

#include <SDL3/SDL.h>

#include <jengine/jengine.hpp>
#include "components/HealthComponent.hpp"

class HealthBarComponent : public Object
{
public:
    HealthBarComponent(Vector position, HealthComponent *health, Vector size);

    void setbackgroundBarColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void setBarColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

private:
    HealthComponent *health = nullptr;

    Vector size;

    SDL_Color backgroundBarColor = {0x36, 0x45, 0x4F, 0x88};

    SquareComponent *backgroundBar = nullptr;

    SDL_Color barColor = {0x25, 0xff, 0x22, 0xFF};

    SquareComponent *bar = nullptr;

    void onHealthChanged(float value);
};
