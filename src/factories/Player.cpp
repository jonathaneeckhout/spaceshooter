#include "cassert"

#include "factories/Player.hpp"
#include "Config.hpp"
#include "components/PlayerInputComponent.hpp"
#include "components/PlayerMovementComponent.hpp"
#include "components/PlayerShootingComponent.hpp"
#include "components/HealthComponent.hpp"
#include "components/HealthBarComponent.hpp"
#include "components/ScoreComponent.hpp"
#include "components/ScoreDisplayComponent.hpp"
#include "components/FPSDisplay.hpp"

namespace
{
    void createVisuals(Object *obj)
    {
        auto wings = jengine::visuals::createSquare(Vector{-(64 / 2), -32 / 2}, Vector(64.0, 32.0), {0x5D, 0x8A, 0xA8, 0xFF});
        obj->addChild(wings);

        auto body = jengine::visuals::createSquare(Vector{-16 / 2, -48}, Vector(16.0, 48.0), {128, 128, 128, 255});
        obj->addChild(body);

        auto leftBlaster = jengine::visuals::createSquare(Vector{-32, -24}, Vector(2.0, 8.0), {128, 128, 128, 255});
        obj->addChild(leftBlaster);

        auto rightBlaster = jengine::visuals::createSquare(Vector{32 - 2, -24}, Vector(2.0, 8.0), {128, 128, 128, 255});
        obj->addChild(rightBlaster);
    }

    Object *createWeaponMuzzle(Vector position)
    {
        auto muzzle = new Object();

        auto transform = new TransformComponent(position);
        muzzle->addChild(transform);

        return muzzle;
    }

    void createUI(Object *obj)
    {
        Vector windowSize = Game::getInstance()->renderer->getWindowSize();

        auto ui = new Object();
        ui->setName("UI");
        obj->addChild(ui);

        auto health = obj->getChild<HealthComponent>();

        auto healtBar = new HealthBarComponent(Vector(windowSize.x - 132, windowSize.y - 48.0), health, Vector(128.0, 32.0));
        ui->addChild(healtBar);

        auto score = obj->getChild<ScoreComponent>();

        auto scoreDisplay = new ScoreDisplayComponent(Vector(16.0, 600 - 48.0), score, 32, "defaultFont");
        ui->addChild(scoreDisplay);

        auto fps = new FPSDisplay(Vector(32.0, 32.0), 32, "defaultFont");
        ui->addChild(fps);
    }
}
namespace spaceshooter
{
    namespace player
    {
        Object *createPlayer(std::string name, Object *map, Vector position)
        {
            assert(map != nullptr && "Missing map object");

            auto obj = new Object();
            obj->setName(name);

            auto transform = new TransformComponent(position);
            obj->addChild(transform);

            Vector size = {64.0, 64.0};

            auto collision = new SquareCollisionComponent(Vector(), size);
            collision->setCentered(true);
            collision->inLayer = Config::PlayerCollisionLayer;
            collision->viewLayer = Config::WorldCollisionLayer;
            obj->addChild(collision);

            auto physics = new PhysicsComponent(transform, collision);
            obj->addChild(physics);

            auto inputs = new PlayerInputComponent();
            obj->addChild(inputs);

            auto movement = new PlayerMovementComponent(transform, physics, inputs);
            obj->addChild(movement);

            auto shooting = new PlayerShootingComponent(inputs, map, Vector(0, -64.0), 0.2f);
            obj->addChild(shooting);

            auto health = new HealthComponent(100.0);
            obj->addChild(health);

            auto score = new ScoreComponent();
            obj->addChild(score);

            createVisuals(obj);

            createUI(obj);

            return obj;
        }
    }
}