#include <iostream>

#include "projectiles/Bullet.hpp"

Bullet::Bullet(Vector position, Vector direction) : Entity(position)
{
    velocity = direction.normalize();

    destroyTimer = new Timer(destroyTime);
    destroyTimer->name = "DestroyTimer";
    destroyTimer->start();

    destroyTimer->setCallback([this](void *)
                              { destroyCallback(); });

    addChild(destroyTimer);

    CollisionShapeSquare *collisionShape = new CollisionShapeSquare(Vector(-2, -2), Vector(4, 4));
    collisionShape->name = "CollisionShape";

    collisionShape->collisionStartHandlers.push_back([this](const std::string collisionshapeID)
                                                     { handleCollisiontStarted(collisionshapeID); });

    addChild(collisionShape);

    createVisuals();
}

Bullet::~Bullet() {}

void Bullet::update(float dt)
{
    Vector newPosition = getPosition() + velocity * speed * dt;
    setPosition(newPosition);
}

void Bullet::createVisuals()
{
    Square *body = new Square(Vector{-2, -2}, 4, 4);

    body->color = {0xA0, 0xFC, 0x24, 255};

    addChild(body);
}

void Bullet::destroyCallback()
{
    queueDelete();
}

void Bullet::handleCollisiontStarted(std::string collisionShapeID)
{
    std::cout << "Bullet hit: " << collisionShapeID << "\n\r";
}
