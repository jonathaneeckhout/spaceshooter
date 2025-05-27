#pragma once

#include <memory>
#include <vector>
#include <jengine/jengine.hpp>

class MainMenu : public Object
{
public:
    MainMenu();
    ~MainMenu();

    void init() override;

private:
    std::shared_ptr<Square> buttonPanel;
    std::shared_ptr<Button> playButton;
    std::shared_ptr<Button> settingsButton;
    std::shared_ptr<Button> quitButton;

    int buttonOffset = 0;

    void registerInputs();
    void createVisuals();

    void handleKeyPress(const std::string &key);

    void selectNextButton(int increment);
};