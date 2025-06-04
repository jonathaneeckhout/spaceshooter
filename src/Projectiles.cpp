#include "Projectiles.hpp"
#include "components/ProjectileComponent.hpp"

namespace spaceshooter
{
    namespace projectiles
    {
        Object *createBullet(Vector position, Vector direction)
        {
            auto obj = new Object();

            auto transform = new TransformComponent(position, direction);
            obj->addComponent(transform);

            auto projectile = new ProjectileComponent(transform, 1200.0, 10.0);
            obj->addComponent(projectile);

            Vector size = Vector(4.0, 8.0);

            auto body = jengine::visuals::createSquare(-size / 2, size, {0xA0, 0xFC, 0x24, 255});
            obj->addChild(body);

            return obj;
        }
    }
}