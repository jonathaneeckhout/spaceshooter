#include "factories/PowerUps.hpp"
#include "Config.hpp"
#include "components/DeleteoffScreenComponent.hpp"
#include "components/LootBehaviorComponent.hpp"

namespace spaceshooter
{
    namespace powerups
    {
        Object *createHealthPack(Vector position)
        {
            auto obj = new Object();
            obj->setName("HealthPack");

            Vector direction = Vector(0, 1);

            Vector size = Vector(16.0, 16.0);

            auto body = new SpriteComponent(Vector(), "healthpack");
            body->centered = true;
            obj->addChild(body);

            auto transform = new TransformComponent(position, direction);
            obj->addChild(transform);

            auto deletion = new DeleteoffScreenComponent(transform);
            obj->addChild(deletion);

            auto collision = new SquareCollisionComponent(Vector(), size);
            collision->setCentered(true);
            collision->inLayer = Config::NoCollisionLayer;
            collision->viewLayer = Config::PlayerCollisionLayer;
            obj->addChild(collision);

            auto behavior = new LootBehaviorComponent(transform, collision, 30.0f);
            obj->addChild(behavior);

            return obj;
        }

    }
}