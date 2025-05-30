#pragma once

#include <string>
#include <jengine/jengine.hpp>
#include "player/HealthBar.hpp"
#include "player/ScoreBar.hpp"

class Player : public Body
{
public:
    class Map *map = nullptr;

    float speed = 400.0;

    Player(Vector position);
    ~Player();

    void init() override;
    void cleanup() override;

    void update(float dt) override;
    void output() override;

    void hurt(float amount);
    void heal(float amount);

    void addScore(unsigned int amount);

private:
    float health = 100.0;
    float maxHealth = health;
    unsigned int score = 0;

    const std::string moveLeftKey = "A";
    const std::string moveRightKey = "D";
    const std::string moveUpKey = "W";
    const std::string moveDownKey = "S";

    const std::string weapon1Key = "Keypad 1";
    const std::string weapon2Key = "Keypad 2";

    const std::string muteMusicKey = "M";

    bool moveLeft = false;
    bool moveRight = false;
    bool moveUp = false;
    bool moveDown = false;

    bool shootWeapon1 = false;
    bool shootWeapon2 = false;

    std::shared_ptr<Entity> weapon1Muzzle;

    float weapon1Delay = 0.2;

    std::shared_ptr<Timer> weapon1Timer;

    std::shared_ptr<Object> UI;

    std::shared_ptr<CollisionShapeSquare> hurtBox;

    std::shared_ptr<CollisionShapeSquare> lootBox;

    std::shared_ptr<HealthBar> healthBar;

    std::shared_ptr<ScoreBar> scoreBar;

    int keyHandlerID = 0;

    void loadEntities();

    void registerControls();
    void deregisterInputs();

    void handleKey(const std::string &key, bool press);

    void createVisuals();

    void updateMovement(float dt);
    void updateShooting(float dt);

    void clampPosition();

    void setHealth(float amount);
};
