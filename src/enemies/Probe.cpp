#include "enemies/Probe.hpp"
#include "Config.hpp"
#include "projectiles/enemies/Zap.hpp"

Probe::Probe(Vector position) : Enemy(position, Vector(0, 1))
{
    speed = 75.0;
    health = 30.0;
    score = 30;
};

Probe::~Probe() {};

void Probe::init()
{

    loadEntities();

    createVisuals();
}

void Probe::loadEntities()
{
    collisionShape = Game::create<CollisionShapeSquare>(Vector(-32, -32), Vector(64, 64));
    collisionShape->setName("CollisionShape");

    collisionShape->inLayer = Config::EnemyCollisionLayer;
    collisionShape->viewLayer = Config::PlayerCollisionLayer;

    addChild(collisionShape);

    weaponTimer = Game::create<Timer>(weaponDelay);
    weaponTimer->setName("WeaponTimer");

    addChild(weaponTimer);
}

void Probe::createVisuals()
{
    auto body = Game::create<Square>(Vector{-32, -32}, Vector(64.0, 64.0));

    body->setColor(0x60, 0x44, 0x39, 255);

    addChild(body);
}

void Probe::update(float dt)
{
    updateMovement(dt);
    updateShooting(dt);
}

void Probe::updateMovement(float dt)
{
    if (deleteOffscreen())
    {
        return;
    }

    Vector newPosition = getPosition() + velocity * speed * dt;

    setPosition(newPosition);
}

void Probe::updateShooting(float)
{
    if (weaponTimer->isRunning())
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