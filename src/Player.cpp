#include "cassert"

#include "Player.hpp"
#include "Config.hpp"
#include "components/PlayerInputComponent.hpp"
#include "components/PlayerMovementComponent.hpp"
#include "components/PlayerShootingComponent.hpp"

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

            auto physics = new PhysicsComponent(transform);
            obj->addChild(physics);

            auto inputs = new PlayerInputComponent();
            obj->addChild(inputs);

            auto movement = new PlayerMovementComponent(transform, physics, inputs);
            obj->addChild(movement);

            auto weapon1Muzzle = createWeaponMuzzle(Vector(0, -64.0));
            obj->addChild(weapon1Muzzle);

            auto weapon1Timer = jengine::utils::createTimer();
            obj->addChild(weapon1Timer);

            auto shooting = new PlayerShootingComponent(inputs, weapon1Muzzle, weapon1Timer, map);
            obj->addChild(shooting);

            createVisuals(obj);

            return obj;
        }
    }
}