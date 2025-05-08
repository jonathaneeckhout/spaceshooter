#include "SpaceShooter.hpp"

SpaceShooter::SpaceShooter()
{
    name = "SpaceShooter";

    Renderer *renderer = Renderer::getInstance();
    if (renderer == nullptr)
    {
        return;
    }

    renderer->setWindowTitle(name);

    game = Game::getInstance();
    if (game == nullptr)
    {
        return;
    }

    loadEntities();

    registerInputs();
}

SpaceShooter::~SpaceShooter() {}

void SpaceShooter::loadEntities()
{
    entities = new Entity();
    entities->name = "Entities";

    game->addChild(entities);

    projectiles = new Entity();
    projectiles->name = "Projectiles";

    entities->addChild(projectiles);

    player = new Player(Vector(400.0, 520.0));
    player->name = "Player";
    player->spaceShooter = this;

    entities->addChild(player);
}

void SpaceShooter::registerInputs()
{
    Controls *controls = Controls::getInstance();
    if (controls == nullptr)
    {
        return;
    }

    controls->keyPressHandlers.push_back([this](std::string key)
                                         { 
        if(key == "Escape") {
            game->stop();
        } });
}

bool SpaceShooter::addProjectile(Entity *projectile)
{
    return projectiles->addChild(projectile);
}