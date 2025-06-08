#include <string>

#include "factories/Maps.hpp"
#include "factories/Player.hpp"
#include "components/QuitOnEscapeComponent.hpp"
#include "factories/Enemies.hpp"

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
            obj->addChild(player);

            // Debug line
            auto enemy = spaceshooter::enemies::createAstroid(Vector(windowSize.x / 2, 64));
            obj->getChildByName("Entities")->addChild(enemy);

            auto enemy1 = spaceshooter::enemies::createAstroid(Vector(600, 64));
            obj->getChildByName("Entities")->addChild(enemy1);

            auto enemy2 = spaceshooter::enemies::createAstroid(Vector(128, 64));
            obj->getChildByName("Entities")->addChild(enemy2);

            return obj;
        }

    }
}
