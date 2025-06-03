#include <string>
#include <iostream>
#include <algorithm>

#include "player/Player.hpp"
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

void Player::cleanup()
{
    deregisterInputs();
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

    lootBox = Game::create<CollisionShapeSquare>(Vector(-32, -32), Vector(64, 64));
    lootBox->setName("LootBox");

    lootBox->inLayer = Config::PowerupCollisionLayer;
    lootBox->viewLayer = Config::NoCollisionLayer;

    addChild(lootBox);

    weapon1Muzzle = Game::create<Entity>(Vector(0, -32));
    weapon1Muzzle->setName("Weapon1Muzzle");

    addChild(weapon1Muzzle);

    weapon1Timer = Game::create<Timer>(weapon1Delay);
    weapon1Timer->setName("Weapon1Timer");

    addChild(weapon1Timer);

    UI = Game::create<Object>();
    UI->setName("UI");
    addChild(UI);

    Vector windowSize = Game::getInstance()->renderer->getWindowSize();

    healthBar = Game::create<HealthBar>(Vector(windowSize.x - 132, windowSize.y - 48.0), health, maxHealth);
    healthBar->setName("HealthBar");

    UI->addChild(healthBar);

    scoreBar = Game::create<ScoreBar>(Vector(16.0, windowSize.y - 48.0));
    scoreBar->setName("ScoreBar");

    UI->addChild(scoreBar);
}

void Player::registerControls()
{
    keyHandlerID = Game::getInstance()->controls->addKeyHandler([this](const std::string &key, bool pressed)
                                                                { handleKey(key, pressed); });
}

void Player::deregisterInputs()
{
    Game::getInstance()->controls->removeKeyHandler(keyHandlerID);
}

void Player::handleKey(const std::string &key, bool press)
{
    auto controls = Game::getInstance()->controls;

    if (controls->isMapping("MoveLeft", key))
    {
        moveLeft = press;
    }
    else if (controls->isMapping("MoveRight", key))
    {
        moveRight = press;
    }
    else if (controls->isMapping("MoveUp", key))
    {
        moveUp = press;
    }
    else if (controls->isMapping("MoveDown", key))
    {
        moveDown = press;
    }
    else if (controls->isMapping("FireWeapon1", key))
    {
        shootWeapon1 = press;
    }
    else if (controls->isMapping("FireWeapon2", key))
    {
        shootWeapon2 = press;
    }
    else if (controls->isMapping("MuteMusic", key))
    {
        if (!press)
        {
            return;
        }

        auto mixer = Game::getInstance()->mixer;
        if (mixer->isMuted())
        {
            mixer->unMute();
        }
        else
        {
            mixer->mute();
        }
    }
}

void Player::createVisuals()
{
    auto wings = Game::create<Square>(Vector{-(64 / 2), -32 / 2}, Vector(64.0, 32.0));
    wings->setColor(0x5D, 0x8A, 0xA8, 0xFF);
    addChild(wings);

    auto body = Game::create<Square>(Vector{-16 / 2, -48}, Vector(16.0, 48.0));
    body->setColor(128, 128, 128, 255);
    addChild(body);

    auto leftBlaster = Game::create<Square>(Vector{-32, -24}, Vector(2.0, 8.0));
    leftBlaster->setColor(128, 128, 128, 255);
    addChild(leftBlaster);

    auto rightBlaster = Game::create<Square>(Vector{32 - 2, -24}, Vector(2.0, 8.0));
    rightBlaster->setColor(128, 128, 128, 255);
    addChild(rightBlaster);
}

void Player::update(float dt)
{
    updateMovement(dt);
    updateShooting(dt);
}

void Player::updateMovement(float dt)
{
    Vector inputDirection;
    if (moveLeft)
    {
        inputDirection.x -= 1;
    }
    if (moveRight)
    {
        inputDirection.x += 1;
    }
    if (moveUp)
    {
        inputDirection.y -= 1;
    }
    if (moveDown)
    {
        inputDirection.y += 1;
    }

    if (inputDirection.magnitude() > 0)
    {
        inputDirection = inputDirection.normalize();

        velocity += inputDirection * accelerationRate * dt;
    }
    else
    {
        if (velocity.magnitude() > 0)
        {
            Vector frictionForce = -velocity.normalize() * friction * dt;
            if (frictionForce.magnitude() > velocity.magnitude())
                velocity = Vector();
            else
                velocity += frictionForce;
        }
    }

    if (velocity.magnitude() > maxSpeed)
    {
        velocity = velocity.normalize() * maxSpeed;
    }

    moveAndStop(dt);

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
    Vector pos = getPosition();

    Vector windowSize = Game::getInstance()->renderer->getWindowSize();

    pos.x = std::clamp<float>(pos.x, 0.0, windowSize.x);
    pos.y = std::clamp<float>(pos.y, 0.0, windowSize.y - 96.0);

    setPosition(pos);
}

void Player::hurt(float amount)
{
    setHealth(health - amount);

    if (health <= 0.0)
    {
        Game::getInstance()->mixer->playSound("PlayerDestroyedExplosion");

        queueDelete();
    }
}

void Player::heal(float amount)
{
    setHealth(health + amount);
}

void Player::setHealth(float amount)
{
    health = std::clamp<float>(amount, 0, maxHealth);

    healthBar->setHealth(health);
}

void Player::addScore(unsigned int amount)
{
    score += amount;

    scoreBar->setScore(score);
}
