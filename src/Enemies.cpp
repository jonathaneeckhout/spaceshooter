#include "Enemies.hpp"
#include "Config.hpp"
#include "components/ProjectileComponent.hpp"
#include "components/HealthComponent.hpp"

namespace spaceshooter
{
    namespace enemies
    {
        Object *createAstroid(Vector position)
        {
            auto obj = new Object();
            obj->setName("Astroid");

            auto transform = new TransformComponent(position, Vector(0, 1));
            obj->addChild(transform);

            Vector size = {64.0, 64.0};

            auto collision = new SquareCollisionComponent(transform, size);
            collision->inLayer = Config::EnemyCollisionLayer;
            collision->viewLayer = Config::PlayerCollisionLayer;
            obj->addChild(collision);

            auto projectile = new ProjectileComponent(transform, collision, 32.0, 30.0);
            obj->addChild(projectile);

            auto body = jengine::visuals::createSquare(-size / 2, size, {0x5A, 0x55, 0x4C, 255});
            obj->addChild(body);

            auto health = new HealthComponent(20.0);
            obj->addChild(health);

            return obj;
        }
    }
}
