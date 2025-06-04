#include "maps/AstroidField.hpp"

#include "enemies/Astroid.hpp"
#include "enemies/Probe.hpp"
#include "enemies/Disc.hpp"

AstroidField::AstroidField() {}

AstroidField::~AstroidField() {}

void AstroidField::loadEnityQueue()
{
    // Vector windowSize = Game::getInstance()->renderer->getWindowSize();

    // for (int i = 0; i < 15; i++)
    // {
    //     float delay = (Game::getInstance()->getRandomFloat() * 1.5) + 0.1;

    //     int amount = (Game::getInstance()->getRandomFloat() * 3) + 1;

    //     std::vector<Entity *> astroids;

    //     for (int j = 0; j < amount; j++)
    //     {
    //         float x = Game::getInstance()->getRandomFloat() * windowSize.x;

    //         astroids.push_back(Game::create<Astroid>(Vector(x, 0)));
    //     }

    //     pushEntityToQueue(delay, astroids);
    // }

    // for (int i = 0; i < 30; i++)
    // {
    //     float delay = (Game::getInstance()->getRandomFloat() * 1.5) + 0.1;

    //     int amount = (Game::getInstance()->getRandomFloat() * 11) + 1;

    //     std::vector<Entity *> astroids;

    //     for (int j = 0; j < amount; j++)
    //     {
    //         float x = Game::getInstance()->getRandomFloat() * windowSize.x;

    //         astroids.push_back(Game::create<Astroid>(Vector(x, 0)));
    //     }

    //     pushEntityToQueue(delay, astroids);
    // }

    // for (int i = 0; i < 15; i++)
    // {
    //     float delay = (Game::getInstance()->getRandomFloat() * 2.5) + 0.5;

    //     int amount = (Game::getInstance()->getRandomFloat() * 4) + 1;

    //     std::vector<Entity *> astroids;

    //     for (int j = 0; j < amount; j++)
    //     {
    //         // At a random x position
    //         float x = Game::getInstance()->getRandomFloat() * windowSize.x;
    //         if (Game::getInstance()->shouldHappen(0.2))
    //         {
    //             astroids.push_back(Game::create<Probe>(Vector(x, 0)));
    //         }
    //         else
    //         {
    //             astroids.push_back(Game::create<Astroid>(Vector(x, 0)));
    //         }
    //     }

    //     pushEntityToQueue(delay, astroids);
    // }

    // auto lastEnemy = Game::create<Disc>(Vector(400, 64));
    // lastEnemy->addDeleteHandler([this]()
    //                             { handleGameEnd(); });

    // pushEntityToQueue(1.0, std::vector<Entity *>{lastEnemy});
}

void AstroidField::playBackgroundSound()
{
    Game::getInstance()->mixer->playSound("backgroundDNB");
}

void AstroidField::stopBackgroundSound()
{
    Game::getInstance()->mixer->stopSound("backgroundDNB");
}
