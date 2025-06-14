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

            auto body = new SquareComponent(Vector(), size, {0xA0, 0xFC, 0x24, 255});
            body->setCentered(true);
            obj->addChild(body);

            auto collision = new SquareCollisionComponent(Vector(), size);
            collision->setCentered(true);

            collision->inLayer = Config::NoCollisionLayer;

            if (isPlayer)
            {
                collision->viewLayer = Config::EnemyCollisionLayer;
            }
            else
            {
                collision->viewLayer = Config::PlayerCollisionLayer;
            }

            obj->addChild(collision);

            auto projectile = new ProjectileComponent(transform, collision, 1200.0, 10.0);
            obj->addChild(projectile);

            auto deletion = new DeleteoffScreenComponent(transform);
            obj->addChild(deletion);

            Game::getInstance()->mixer->playSound("bullet");

            return obj;
        }

        Object *createZap(Vector position, Vector direction, bool isPlayer)
        {
            auto obj = new Object();
            obj->setName("Zap");

            auto transform = new TransformComponent(position, direction);
            obj->addChild(transform);

            Vector size = Vector(4.0, 8.0);

            auto body = new SquareComponent(Vector(), size, {0xAA, 0x22, 0xCC, 255});
            body->setCentered(true);
            obj->addChild(body);

            auto collision = new SquareCollisionComponent(Vector(), size);
            collision->setCentered(true);

            collision->inLayer = Config::NoCollisionLayer;

            if (isPlayer)
            {
                collision->viewLayer = Config::EnemyCollisionLayer;
            }
            else
            {
                collision->viewLayer = Config::PlayerCollisionLayer;
            }

            obj->addChild(collision);

            auto projectile = new ProjectileComponent(transform, collision, 300.0, 10.0);
            obj->addChild(projectile);

            auto deletion = new DeleteoffScreenComponent(transform);
            obj->addChild(deletion);

            Game::getInstance()->mixer->playSound("zap");

            return obj;
        }
    }
}