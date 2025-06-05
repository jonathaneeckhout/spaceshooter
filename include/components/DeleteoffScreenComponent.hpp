#pragma once

#include <jengine/jengine.hpp>

class DeleteoffScreenComponent : public Object
{
public:
    DeleteoffScreenComponent(TransformComponent *transform, Vector buffer = {64.0, 64.0});

    void update(float dt) override;

private:
    TransformComponent *transform;
    Vector buffer;
};