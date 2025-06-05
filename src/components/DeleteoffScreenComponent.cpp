#include "components/DeleteoffScreenComponent.hpp"

DeleteoffScreenComponent::DeleteoffScreenComponent(
    TransformComponent *transform,
    Vector buffer)
    : transform(transform),
      buffer(buffer) {}

void DeleteoffScreenComponent::update(float)
{
    auto pos = transform->getGlobalPosition();

    Vector windowSize = Game::getInstance()->renderer->getWindowSize();

    const float leftBound = -buffer.x;
    const float rightBound = windowSize.x + buffer.x;
    const float topBound = -buffer.y;
    const float bottomBound = windowSize.y + buffer.y;

    if (pos.x < leftBound || pos.x > rightBound || pos.y < topBound || pos.y > bottomBound)
    {
        getParent()->queueDelete();
    }
}
