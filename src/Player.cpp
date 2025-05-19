#include <string>
#include <iostream>
#include <algorithm>

#include "Player.hpp"
#include "projectiles/player/Bullet.hpp"
#include "maps/Map.hpp"
#include "Config.hpp"

Player::Player(Vector position) : Body(position) {}

Player::~Player() {}

void Player::init()
{
    loadEntities();

    registerControls();

    createVisuals();
}

void Player::loadEntities()
{
    collisionShape = Game::create<CollisionShapeSquare>(Vector(-16, -16), Vector(32, 32));
    collisionShape->setName("CollisionShape");

    collisionShape->inLayer = Config::WorldCollisionLayer;
    collisionShape->viewLayer = Config::WorldCollisionLayer;

    addChild(collisionShape);

    hurtBox = Game::create<CollisionShapeSquare>(Vector(-16, -16), Vector(32, 32));
    hurtBox->setName("HurtBox");

    hurtBox->inLayer = Config::PlayerCollisionLayer;
    hurtBox->viewLayer = Config::NoCollisionLayer;

    addChild(hurtBox);

    weapon1Muzzle = Game::create<Entity>(Vector(0, -32));
    weapon1Muzzle->setName("Weapon1Muzzle");

    addChild(weapon1Muzzle);

    weapon1Timer = Game::create<Timer>(weapon1Delay);
    weapon1Timer->setName("Weapon1Timer");

    addChild(weapon1Timer);
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
    auto wings = Game::create<Square>(Vector{-(64 / 2), -32 / 2}, 64, 32);
    wings->color = {0x5D, 0x8A, 0xA8, 0xFF};
    addChild(wings);

    auto body = Game::create<Square>(Vector{-16 / 2, -48}, 16, 48);
    body->color = {128, 128, 128, 255};
    addChild(body);

    auto leftBlaster = Game::create<Square>(Vector{-32, -24}, 2, 8);
    leftBlaster->color = {128, 128, 128, 255};
    addChild(leftBlaster);

    auto rightBlaster = Game::create<Square>(Vector{32 - 2, -24}, 2, 8);
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

    if (getPosition().y < 500)
    {
        velocity += backDraw;
    }

    velocity *= speed;

    moveAndStop(dt);

    // Clamp position to the window's size
    clampPosition();
}

void Player::updateShooting(float)
{
    if (shootWeapon1)
    {
        if (weapon1Timer->isRunning())
        {
            return;
        }

        weapon1Timer->start();

        auto bullet = Game::create<Bullet>(weapon1Muzzle->getGlobalPosition(), Vector(0.0, -1.0));

        map->addProjectile(bullet);
    }

    if (shootWeapon2)
    {
        std::cout << "Firing weapon 2!" << std::endl;
    }
}

void Player::output() {}

void Player::clampPosition()
{
    Renderer *renderer = Renderer::getInstance();

    Vector pos = getPosition();

    pos.x = std::clamp<float>(pos.x, 0.0, renderer->windowSize.x);
    pos.y = std::clamp<float>(pos.y, 0.0, renderer->windowSize.y);

    setPosition(pos);
}

void Player::hurt(float amount)
{
    health -= amount;

    if (health <= 0.0)
    {
        health = 0.0;

        std::cout << "Goodbye Cruel World!\n\r";

        queueDelete();
    }
}
