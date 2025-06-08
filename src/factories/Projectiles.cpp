#include "factories/Projectiles.hpp"
#include "Config.hpp"
#include "components/ProjectileComponent.hpp"
#include "components/DeleteoffScreenComponent.hpp"

namespace spaceshooter
{
    namespace projectiles
    {
        Object *createBullet(Vector position, Vector direction, bool isPlayer)
        {
            auto obj = new Object();
            obj->setName("Bullet");

            auto transform = new TransformComponent(position, direction);
            obj->addChild(transform);

            Vector size = Vector(4.0, 8.0);

            auto body = jengine::visuals::createSquare(-size / 2, size, {0xA0, 0xFC, 0x24, 255});
            obj->addChild(body);

            auto collision = new SquareCollisionComponent(transform, size);
            collision->inLayer = Config::NoCollisionLayer;

            if (isPlayer)
            {
                collision->viewLayer = Config::EnemyCollisionLayer;
            }
            else
            {
                collision->viewLayer = Config::PlayerCollisionLayer;
            }

            collision->center = true;

            obj->addChild(collision);

            auto projectile = new ProjectileComponent(transform, collision, 1200.0, 10.0);
            obj->addChild(projectile);

            auto deletion = new DeleteoffScreenComponent(transform);
            obj->addChild(deletion);

            return obj;
        }
    }
}