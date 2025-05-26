#pragma once

#include <jengine/jengine.hpp>

class MainMenu : public Object
{
public:
    MainMenu();
    ~MainMenu();

    void init() override;

private:
    void createVisuals();
};