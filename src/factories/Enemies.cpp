#include "factories/Enemies.hpp"
#include "Config.hpp"
#include "components/ProjectileComponent.hpp"
#include "components/HealthComponent.hpp"
#include "components/GiveScoreComponent.hpp"
#include "components/LootComponent.hpp"
#include "factories/PowerUps.hpp"
#include "components/DeleteoffScreenComponent.hpp"

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

            auto collision = new SquareCollisionComponent(Vector(), size);
            collision->inLayer = Config::EnemyCollisionLayer;
            collision->viewLayer = Config::PlayerCollisionLayer;
            collision->setCentered(true);
            obj->addChild(collision);

            auto projectile = new ProjectileComponent(transform, collision, 400.0, 30.0);
            obj->addChild(projectile);

            auto deletion = new DeleteoffScreenComponent(transform);
            obj->addChild(deletion);

            auto body = new SquareComponent(Vector(), size, {0x5A, 0x55, 0x4C, 255});
            body->setCentered(true);
            obj->addChild(body);

            auto health = new HealthComponent(20.0);
            obj->addChild(health);

            auto giveScore = new GiveScoreComponent(health, 5);
            obj->addChild(giveScore);

            auto loot = new LootComponent(transform, health);

            std::function<Object *(Vector)> lootFunc = [](Vector pos)
            {
                return spaceshooter::powerups::createHealthPack(pos);
            };

            loot->setLoot(lootFunc, 0.1);

            obj->addChild(loot);

            return obj;
        }
    }
}
