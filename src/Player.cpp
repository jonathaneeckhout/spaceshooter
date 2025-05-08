#include <string>
#include <iostream>

#include "Player.hpp"
#include "Bullet.hpp"
#include "SpaceShooter.hpp"

Player::Player(Vector position) : Entity(position)
{
    loadEntities();

    registerControls();

    createVisuals();
}

Player::~Player() {}

void Player::loadEntities()
{
    weapon1Muzzle = new Entity(Vector(0, -32));
    weapon1Muzzle->name = "Weapon1Muzzle";

    addChild(weapon1Muzzle);
}

void Player::registerControls()
{
    Controls *controls = Controls::getInstance();
    if (controls == nullptr)
    {
        return;
    }

    controls->keyPressHandlers.push_back([this](const std::string &key)
                                         { handleKeyPress(key); });

    controls->keyReleaseHandlers.push_back([this](const std::string &key)
                                           { handleKeyRelease(key); });
}

void Player::handleKeyPress(const std::string &key)
{
    if (key == moveLeftKey)
    {
        moveLeft = true;
    }
    else if (key == moveRightKey)
    {
        moveRight = true;
    }
    else if (key == moveUpKey)
    {
        moveUp = true;
    }
    else if (key == moveDownKey)
    {
        moveDown = true;
    }
    else if (key == weapon1Key)
    {
        shootWeapon1 = true;
    }
    else if (key == weapon2Key)
    {
        shootWeapon2 = true;
    }
}

void Player::handleKeyRelease(const std::string &key)
{
    if (key == moveLeftKey)
    {
        moveLeft = false;
    }
    else if (key == moveRightKey)
    {
        moveRight = false;
    }
    else if (key == moveUpKey)
    {
        moveUp = false;
    }
    else if (key == moveDownKey)
    {
        moveDown = false;
    }
    else if (key == weapon1Key)
    {
        shootWeapon1 = false;
    }
    else if (key == weapon2Key)
    {
        shootWeapon2 = false;
    }
}

void Player::createVisuals()
{
    Square *wings = new Square(Vector{-(64 / 2), -32 / 2}, 64, 32);
    addChild(wings);

    Square *body = new Square(Vector{-16 / 2, -48}, 16, 48);
    body->color = {128, 128, 128, 255};
    addChild(body);

    Square *leftBlaster = new Square(Vector{-32, -24}, 2, 8);
    leftBlaster->color = {128, 128, 128, 255};
    addChild(leftBlaster);

    Square *rightBlaster = new Square(Vector{32 - 2, -24}, 2, 8);
    rightBlaster->color = {128, 128, 128, 255};
    addChild(rightBlaster);
}

void Player::update(float dt)
{
    updateMovement(dt);
    updateShooting(dt);
}

void Player::updateMovement(float dt)
{
    velocity = Vector();

    if (moveLeft)
    {
        velocity.x -= 1;
    }
    if (moveRight)
    {
        velocity.x += 1;
    }
    if (moveUp)
    {
        velocity.y -= 1;
    }
    if (moveDown)
    {
        velocity.y += 1;
    }

    velocity = velocity.normalize();

    Vector newPosition = getPosition() + (velocity * speed * dt);

    setPosition(newPosition);
}

void Player::updateShooting(float)
{
    if (shootWeapon1)
    {
        std::cout << "Firing weapon 1!" << std::endl;
        Bullet *bullet = new Bullet(weapon1Muzzle->getGlobalPosition(), Vector(0.0, -1.0));

        spaceShooter->addProjectile(bullet);
    }

    if (shootWeapon2)
    {
        std::cout << "Firing weapon 2!" << std::endl;
    }
}

void Player::output() {}