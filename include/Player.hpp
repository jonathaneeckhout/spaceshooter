#pragma once

#include <string>
#include <jengine/jengine.hpp>

// Forward declare SpaceShooter to avoid circular include
class SpaceShooter;

class Player : public Entity
{
public:
    float speed = 300.0;

    SpaceShooter *spaceShooter = nullptr;

    Player(Vector position);
    ~Player();

    void update(float dt) override;
    void output() override;

private:
    const std::string moveLeftKey = "A";
    const std::string moveRightKey = "D";
    const std::string moveUpKey = "W";
    const std::string moveDownKey = "S";

    const std::string weapon1Key = "Keypad 1";
    const std::string weapon2Key = "Keypad 2";

    bool moveLeft = false;
    bool moveRight = false;
    bool moveUp = false;
    bool moveDown = false;

    bool shootWeapon1 = false;
    bool shootWeapon2 = false;

    Entity *weapon1Muzzle = nullptr;

    float weapon1Delay = 0.2;

    Timer *weapon1Timer = nullptr;

    void loadEntities();

    void registerControls();
    void handleKeyPress(const std::string &key);
    void handleKeyRelease(const std::string &key);

    void createVisuals();

    void updateMovement(float dt);
    void updateShooting(float dt);
};