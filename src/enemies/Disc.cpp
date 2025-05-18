#include "enemies/Disc.hpp"
#include "Config.hpp"
#include "Player.hpp"
#include "projectiles/enemies/Zap.hpp"
#include "SpaceShooter.hpp"

Disc::Disc(Vector position) : Enemy(position)
{
    speed = 100.0;
    health = 10.0;
    velocity = Vector(1.0, 0.0);
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
    auto body = Game::create<Square>(Vector{-16, -16}, 32, 32);

    body->color = {0x7A, 0xD0, 0xB2, 255};

    addChild(body);
}

void Disc::update(float dt)
{
    updateMovement(dt);
    updateShooting(dt);
}



void Disc::updateMovement(float dt)
{
    auto pos = getPosition();

    if (pos.x > 700)
    {
        velocity.x = -1.0;
    }
    else if (pos.x < 100)
    {
        velocity.x = 1.0;
    }

    velocity = velocity.normalize();

    Vector newPosition = pos + velocity * speed * dt;

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

    auto entities = static_cast<SpaceShooter *>(parent.lock().get());

    auto spaceShooter = static_cast<SpaceShooter *>(entities->getParent().lock().get());

    auto player = spaceShooter->getPlayer().lock().get();

    auto zap = Game::create<Zap>(getGlobalPosition(), getGlobalPosition().directionTo(player->getGlobalPosition()));

    spaceShooter->addProjectile(zap);
}