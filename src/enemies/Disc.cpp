#include "enemies/Disc.hpp"
#include "Config.hpp"
#include "player/Player.hpp"
#include "projectiles/enemies/Zap.hpp"
#include "maps/Map.hpp"

Disc::Disc(Vector position) : Enemy(position)
{
    speed = 100.0;
    health = 30.0;
    velocity = Vector(1.0, 0.0);
    score = 30;
};

Disc::~Disc() {};

void Disc::init()
{
    loadEntities();

    createVisuals();
}

void Disc::loadEntities()
{
    collisionShape = Game::create<CollisionShapeSquare>(Vector(-16, -16), Vector(32, 32));
    collisionShape->setName("CollisionShape");

    collisionShape->inLayer = Config::EnemyCollisionLayer;
    collisionShape->viewLayer = Config::PlayerCollisionLayer;

    addChild(collisionShape);

    weaponTimer = Game::create<Timer>(weaponDelay);
    weaponTimer->setName("WeaponTimer");

    addChild(weaponTimer);
}

void Disc::createVisuals()
{
    auto body = Game::create<Square>(Vector{-16, -16}, Vector(32.0, 32.0));

    body->setColor(0x7A, 0xD0, 0xB2, 255);

    addChild(body);
}

void Disc::update(float dt)
{
    updateMovement(dt);
    updateShooting(dt);
}

void Disc::updateMovement(float dt)
{
    if (deleteOffscreen())
    {
        return;
    }

    auto pos = getPosition();

    Vector movement(0.0f, 0.0f);

    if (movingDown)
    {
        float dropStep = speed * dt;
        if (dropStep >= remainingDropDistance)
        {
            movement.y = remainingDropDistance;
            remainingDropDistance = 0.0f;
            movingDown = false;
        }
        else
        {
            movement.y = dropStep;
            remainingDropDistance -= dropStep;
        }
    }
    else
    {
        // Check for edge collision
        if (goingRight && pos.x > 700)
        {
            goingRight = false;
            movingDown = true;
            remainingDropDistance = 128.0f;
        }
        else if (!goingRight && pos.x < 100)
        {
            goingRight = true;
            movingDown = true;
            remainingDropDistance = 96.0f;
        }

        movement.x = (goingRight ? 1.0f : -1.0f) * speed * dt;
    }

    Vector newPosition = pos + movement;
    setPosition(newPosition);
}

void Disc::updateShooting(float)
{
    if (weaponTimer->isRunning())
    {
        return;
    }

    if (!parent.lock())
    {
        return;
    }

    weaponTimer->start();

    auto player = getPlayer();
    if (!player)
    {
        return;
    }

    if (!player->isPartOfGame())
    {
        return;
    }

    auto map = getMap();
    if (!map)
    {
        return;
    }

    auto zap = Game::create<Zap>(getGlobalPosition(), getGlobalPosition().directionTo(player->getGlobalPosition()));

    map->addProjectile(zap);
}