#include <string>
#include <iostream>

#include "factories/Maps.hpp"
#include "factories/Player.hpp"
#include "factories/Enemies.hpp"
#include "factories/Menus.hpp"
#include "components/QuitOnEscapeComponent.hpp"
#include "components/ObjectQueueComponent.hpp"
#include "components/GameEndComponent.hpp"

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

            auto background = new ParallaxComponent(Vector(), Vector(0.0, -1.0), 20.f, "stars");
            obj->addChild(background);

            loadGrouping(obj, "Entities");
            loadGrouping(obj, "Projectiles");
            loadGrouping(obj, "Powerups");

            Vector windowSize = Game::getInstance()->renderer->getWindowSize();

            auto player = spaceshooter::player::createPlayer("Player", obj, Vector(windowSize.x / 2, windowSize.y - 80));

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

            auto lastEnemy = spaceshooter::enemies::createAstroid(Vector(windowSize.x / 2, 0));
            objectQueue->pushEntityToQueue(1.0, std::vector<Object *>{lastEnemy});

            auto gameEnd = new GameEndComponent(player, lastEnemy, 3.0);
            std::function<void(bool, unsigned int)> gameEndHanlder = [objectQueue](bool won, unsigned int score)
            {
                objectQueue->stop();

                auto gameEndedMenu = spaceshooter::menus::createGameEndedMenu(won, score);
                Game::getInstance()->setRootObject(gameEndedMenu);
            };

            gameEnd->addEventHandler("onGameEnded", gameEndHanlder);
            obj->addChild(gameEnd);

            auto soundLoader = new SoundLoaderComponent();
            soundLoader->addSound("backgroundDNB", "backgroundDNB");
            soundLoader->addSound("bullet", "bullet");
            soundLoader->addSound("bulletImpact", "bulletImpact", 0.8);
            soundLoader->addSound("zap", "zap", 0.8);
            soundLoader->addSound("ZapImpact", "ZapImpact");
            soundLoader->addSound("powerup", "powerup");
            soundLoader->addSound("EnemyDestroyedExplosion", "explosion0", 0.7);
            soundLoader->addSound("PlayerDestroyedExplosion", "explosion1");
            obj->addChild(soundLoader);

            Game::getInstance()->mixer->playSound("backgroundDNB");

            return obj;
        }

    }
}
