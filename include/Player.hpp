#pragma once

#include <string>
#include <jengine/jengine.hpp>

// Forward declare SpaceShooter to avoid circular include
class SpaceShooter;

class Player : public Body
{
public:
    SpaceShooter *spaceShooter = nullptr;

    float speed = 300.0;

    Player(Vector position);
    ~Player();

    void init() override;

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

    Vector backDraw = Vector(0.0, 0.4);

    bool shootWeapon1 = false;
    bool shootWeapon2 = false;

    std::shared_ptr<Entity> weapon1Muzzle = nullptr;

    float weapon1Delay = 0.2;

    std::shared_ptr<Timer> weapon1Timer = nullptr;

    void loadEntities();

    void registerControls();
    void handleKeyPress(const std::string &key);
    void handleKeyRelease(const std::string &key);

    void createVisuals();

    void updateMovement(float dt);
    void updateShooting(float dt);

    void clampPosition();
};