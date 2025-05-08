#include "Bullet.hpp"

Bullet::Bullet(Vector position, Vector direction) : Entity(position)
{
    velocity = direction.normalize();

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
    Square *body = new Square(Vector{-2, -4}, 4, 8);

    body->color = {0xA0, 0xFC, 0x24, 255};

    addChild(body);
}
