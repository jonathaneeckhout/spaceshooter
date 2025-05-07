#pragma once

#include <string>
#include <jengine/entities/Entity.hpp>

class Player : public Entity
{
public:
    float speed = 300.0;

    Player();
    ~Player();

    void update(float dt) override;
    void output() override;

private:
    const std::string moveLeftKey = "A";
    const std::string moveRightKey = "D";
    const std::string moveUpKey = "W";
    const std::string moveDownKey = "S";

    bool moveLeft = false;
    bool moveRight = false;
    bool moveUp = false;
    bool moveDown = false;

    void registerControls();
    void handleKeyPress(const std::string& key);
    void handleKeyRelease(const std::string& key);

    void createVisuals();
};