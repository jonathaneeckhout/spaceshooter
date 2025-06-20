#include "factories/Enemies.hpp"
#include "Config.hpp"
#include "components/ProjectileComponent.hpp"
#include "components/HealthComponent.hpp"
#include "components/GiveScoreComponent.hpp"
#include "components/LootComponent.hpp"
#include "factories/PowerUps.hpp"
#include "components/DeleteoffScreenComponent.hpp"
#include "components/EnemyShootComponent.hpp"

namespace spaceshooter
{
    namespace enemies
    {
        Object *createAstroid(Vector position)
        {
            Vector size = {64.0, 64.0};
            float speed = 300.0f;
            float damage = 30.0f;
            float maxHealth = 20.0f;
            unsigned int score = 5;

            auto obj = new Object();
            obj->setName("Astroid");

            auto transform = new TransformComponent(position, Vector(0, 1));
            obj->addChild(transform);

            auto collision = new SquareCollisionComponent(Vector(), size);
            collision->inLayer = Config::EnemyCollisionLayer;
            collision->viewLayer = Config::PlayerCollisionLayer;
            collision->setCentered(true);
            obj->addChild(collision);

            auto projectile = new ProjectileComponent(transform, collision, speed, damage);
            obj->addChild(projectile);

            auto deletion = new DeleteoffScreenComponent(transform);
            obj->addChild(deletion);

            auto body = new SpriteComponent(Vector(), "astroid");
            body->centered = true;
            obj->addChild(body);

            auto health = new HealthComponent(maxHealth);
            obj->addChild(health);

            auto giveScore = new GiveScoreComponent(health, score);
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

        Object *createProbe(Vector position)
        {
            Vector size = {64.0, 64.0};
            float speed = 75.0f;
            float damage = 10.0f;
            float maxHealth = 50.0f;
            unsigned int score = 15;

            auto obj = new Object();
            obj->setName("Probe");

            auto transform = new TransformComponent(position, Vector(0, 1));
            obj->addChild(transform);

            auto collision = new SquareCollisionComponent(Vector(), size);
            collision->inLayer = Config::EnemyCollisionLayer;
            collision->viewLayer = Config::PlayerCollisionLayer;
            collision->setCentered(true);
            obj->addChild(collision);

            auto projectile = new ProjectileComponent(transform, collision, speed, damage);
            obj->addChild(projectile);

            auto deletion = new DeleteoffScreenComponent(transform);
            obj->addChild(deletion);

            auto body = new SpriteComponent(Vector(), "probe");
            body->centered = true;
            obj->addChild(body);

            auto health = new HealthComponent(maxHealth);
            obj->addChild(health);

            auto giveScore = new GiveScoreComponent(health, score);
            obj->addChild(giveScore);

            auto shooter = new EnemyShootComponent(Vector(0, 16.0), 1.0);
            obj->addChild(shooter);

            return obj;
        }

        Object *createDisc(Vector position)
        {
            Vector size = {64.0, 64.0};
            float speed = 75.0f;
            float damage = 15.0f;
            float maxHealth = 60.0f;
            unsigned int score = 30;

            auto obj = new Object();
            obj->setName("Disc");

            auto transform = new TransformComponent(position, Vector(0, 1));
            obj->addChild(transform);

            auto collision = new SquareCollisionComponent(Vector(), size);
            collision->inLayer = Config::EnemyCollisionLayer;
            collision->viewLayer = Config::PlayerCollisionLayer;
            collision->setCentered(true);
            obj->addChild(collision);

            auto projectile = new ProjectileComponent(transform, collision, speed, damage);
            obj->addChild(projectile);

            auto deletion = new DeleteoffScreenComponent(transform);
            obj->addChild(deletion);

            auto body = new SpriteComponent(Vector(), "disc");
            body->centered = true;
            obj->addChild(body);

            auto health = new HealthComponent(maxHealth);
            obj->addChild(health);

            auto giveScore = new GiveScoreComponent(health, score);
            obj->addChild(giveScore);

            auto shooter = new EnemyShootComponent(Vector(0, 16.0), 1.0);
            obj->addChild(shooter);

            return obj;
        }
    }
}
