#include <string>
#include <iostream>

#include "factories/Maps.hpp"
#include "factories/Player.hpp"
#include "factories/Enemies.hpp"
#include "factories/Menus.hpp"
#include "components/QuitOnEscapeComponent.hpp"
#include "components/ObjectQueueComponent.hpp"
#include "components/GameEndComponent.hpp"
#include "Spaceshooter.hpp"

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

            Spaceshooter::getInstance()->setMap(obj);

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

            Spaceshooter::getInstance()->setPlayer(player);

            std::function<void()> playerDiedHandler = []()
            {
                Spaceshooter::getInstance()->setPlayer(nullptr);
            };

            player->addEventHandler("onDeleted", playerDiedHandler);

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

            // Second wave a bunch of astroid and discs
            for (int i = 0; i < 15; i++)
            {
                float delay = (Game::getInstance()->getRandomFloat() * 2.5) + 0.5;

                int amount = (Game::getInstance()->getRandomFloat() * 4) + 1;

                std::vector<Object *> astroids;

                for (int j = 0; j < amount; j++)
                {
                    // At a random x position
                    float x = Game::getInstance()->getRandomFloat() * windowSize.x;
                    if (Game::getInstance()->shouldHappen(0.2))
                    {
                        astroids.push_back(spaceshooter::enemies::createProbe(Vector(x, 0)));
                    }
                    else
                    {
                        astroids.push_back(spaceshooter::enemies::createAstroid(Vector(x, 0)));
                    }
                }

                objectQueue->pushEntityToQueue(delay, astroids);
            }

            // Third wave: Mix of asteroids, probes, and disc enemies
            for (int i = 0; i < 15; i++)
            {
                float delay = (Game::getInstance()->getRandomFloat() * 3.0f) + 0.5f;

                int amount = (Game::getInstance()->getRandomFloat() * 5) + 2;

                std::vector<Object *> enemies;

                for (int j = 0; j < amount; j++)
                {
                    float x = Game::getInstance()->getRandomFloat() * windowSize.x;

                    float rand = Game::getInstance()->getRandomFloat();

                    if (rand < 0.15f)
                    {
                        // 15% chance to spawn new disc enemy
                        enemies.push_back(spaceshooter::enemies::createDisc(Vector(x, 0)));
                    }
                    else if (rand < 0.35f)
                    {
                        // 20% chance to spawn a probe
                        enemies.push_back(spaceshooter::enemies::createProbe(Vector(x, 0)));
                    }
                    else
                    {
                        // 65% chance to spawn an asteroid
                        enemies.push_back(spaceshooter::enemies::createAstroid(Vector(x, 0)));
                    }
                }

                objectQueue->pushEntityToQueue(delay, enemies);
            }

            auto lastEnemy = spaceshooter::enemies::createAstroid(Vector(windowSize.x / 2, 0));
            objectQueue->pushEntityToQueue(1.0, std::vector<Object *>{lastEnemy});

            auto gameEnd = new GameEndComponent(player, lastEnemy, 3.0);
            std::function<void(bool, unsigned int)> gameEndHanlder = [objectQueue](bool won, unsigned int score)
            {
                objectQueue->stop();

                auto gameEndedMenu = spaceshooter::menus::createGameEndedMenu(won, score);
                Game::getInstance()->setRootObject(gameEndedMenu);

                Spaceshooter::getInstance()->setMap(nullptr);
                Spaceshooter::getInstance()->setPlayer(nullptr);
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

            auto muter = new MuteComponent("MuteMusic");
            obj->addChild(muter);

            return obj;
        }

    }
}
