#pragma once

#include <jengine/jengine.hpp>
#include "player/Player.hpp"

class Powerup : public Entity
{
public:
    Powerup(Vector position);
    ~Powerup();

    void init() override;

    void update(float dt) override;

protected:
    float speed = 100.0f;

    float destroyTime = 4.0;

    Timer *destroyTimer = nullptr;

    virtual void loadEntities();

    virtual void createVisuals();

    virtual void applyEffect(Player *player);

private:
    void destroyCallback();

    void handleCollisiontStarted(CollisionShape *shape);
};