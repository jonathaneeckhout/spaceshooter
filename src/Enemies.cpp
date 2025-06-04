#include "Enemies.hpp"

namespace enemies
{
    Object *createAstroid(Vector position)
    {
        auto obj = new Object();

        auto transform = new TransformComponent(position);
        obj->addComponent(transform);

        Vector size = {64.0, 64.0};

        auto collisionShape = new CollisionShapeSquare(-size / 2, size);

        auto physics = new PhysicsComponent(transform, collisionShape);
        obj->addComponent(physics);

        auto body = new Square(-size / 2, size);
        body->setColor(0x5A, 0x55, 0x4C, 255);

        obj->addChild(body);

        return obj;
    }
}
