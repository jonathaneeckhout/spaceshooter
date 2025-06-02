#pragma once

#include <vector>
#include <jengine/jengine.hpp>

class MainMenu : public Object
{
public:
    MainMenu();
    ~MainMenu();

    void init() override;
    void cleanup() override;

private:
    Text *title = nullptr;

    Square *buttonPanel = nullptr;

    TextButton *playButton = nullptr;
    TextButton *settingsButton = nullptr;
    TextButton *quitButton = nullptr;

    int buttonOffset = 0;
    int keyHandlerID = 0;

    void registerInputs();
    void deregisterInputs();
    void createVisuals();

    void handleKey(const std::string &key, bool pressed);
    void handlePlay();
    void handleSettings();
    void handleQuit();

    void selectNextButton(int increment, bool playSound);
    void pressSelectedButton();
};