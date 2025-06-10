#include <string>

#include "factories/Maps.hpp"
#include "factories/Player.hpp"
#include "factories/Enemies.hpp"
#include "components/QuitOnEscapeComponent.hpp"
#include "components/ObjectQueueComponent.hpp"

namespace
{
    void loadGrouping(Object *obj, const std::string &name)
    {
        auto grouping = new Object();
        grouping->setName(name);

        obj->addChild(grouping);
    }
}
namespace spaceshooter
{
    namespace maps
    {
        Object *createAstroidField()
        {
            Object *obj = new Object();

            auto transform = new TransformComponent(Vector());
            obj->addChild(transform);

            auto quit = new QuitOnEscapeComponent();
            obj->addChild(quit);

            loadGrouping(obj, "Entities");
            loadGrouping(obj, "Projectiles");
            loadGrouping(obj, "Powerups");

            Vector windowSize = Game::getInstance()->renderer->getWindowSize();

            auto player = spaceshooter::player::createPlayer("Player", obj, Vector(windowSize.x / 2, windowSize.y - 80));
            // auto player = spaceshooter::player::createPlayer("Player", obj, Vector(0,0));

            obj->addChild(player);

            auto objectQueue = new ObjectQueueComponent(obj->getChildByName("Entities"));
            obj->addChild(objectQueue);

            // First wave is a bunch of astroids the player needs to avoid
            for (int i = 0; i < 15; i++)
            {
                float delay = (Game::getInstance()->getRandomFloat() * 1.5) + 0.1;

                int amount = (Game::getInstance()->getRandomFloat() * 3) + 1;

                std::vector<Object *> astroids;

                for (int j = 0; j < amount; j++)
                {
                    float x = Game::getInstance()->getRandomFloat() * windowSize.x;

                    astroids.push_back(spaceshooter::enemies::createAstroid(Vector(x, 0)));
                }

                objectQueue->pushEntityToQueue(delay, astroids);
            }

            return obj;
        }

    }
}
