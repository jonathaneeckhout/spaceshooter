#include <string>

#include "Maps.hpp"
#include "Player.hpp"
#include "components/QuitOnEscapeComponent.hpp"

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
            obj->addComponent(transform);

            auto quit = new QuitOnEscapeComponent();
            obj->addComponent(quit);

            loadGrouping(obj, "Entities");
            loadGrouping(obj, "Projectiles");
            loadGrouping(obj, "Powerups");

            Vector windowSize = Game::getInstance()->renderer->getWindowSize();

            auto player = spaceshooter::player::createPlayer("Player", obj, Vector(windowSize.x / 2, windowSize.y - 80));
            obj->addChild(player);

            return obj;
        }

    }
}
