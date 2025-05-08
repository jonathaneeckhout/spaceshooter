#include "enemies/Astroid.hpp"

Astroid::Astroid(Vector position) : Enemy(position, Vector(0, 1))
{
    speed = 150.0;

    destroyTimer = new Timer(destroyTime);
    destroyTimer->name = "DestroyTimer";
    destroyTimer->start();

    destroyTimer->setCallback([this](void *)
                              { destroyCallback(); });

    addChild(destroyTimer);

    loadEntities();

    createVisuals();
}

Astroid::~Astroid() {}

void Astroid::loadEntities()
{
}

void Astroid::createVisuals()
{
    Square *body = new Square(Vector{-16, -16}, 32, 32);

    body->color = {0x5A, 0x55, 0x4C, 255};

    addChild(body);
}

void Astroid::update(float dt)
{
    Vector newPosition = getPosition() + velocity * speed * dt;

    setPosition(newPosition);
}

void Astroid::destroyCallback()
{
    queueDelete();
}