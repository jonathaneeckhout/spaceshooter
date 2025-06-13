#include "Spaceshooter.hpp"

Spaceshooter *Spaceshooter::instancePtr = nullptr;

Spaceshooter::Spaceshooter() {}

Spaceshooter::~Spaceshooter() {}

Spaceshooter *Spaceshooter::getInstance()
{
    if (instancePtr == nullptr)
    {
        instancePtr = new Spaceshooter();
    }

    return instancePtr;
}

void Spaceshooter::deleteInstance()
{
    if (instancePtr != nullptr)
    {
        delete instancePtr;
        instancePtr = nullptr;
    }
}

Vector Spaceshooter::directionToPlayer(Vector position)
{
    if (player == nullptr)
    {
        return Vector();
    }

    auto playerTransform = player->getChild<TransformComponent>();
    if (playerTransform == nullptr)
    {
        return Vector();
    }

    return position.directionTo(playerTransform->getGlobalPosition());
}