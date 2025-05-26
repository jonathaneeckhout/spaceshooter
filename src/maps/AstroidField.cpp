#include "maps/AstroidField.hpp"

#include "enemies/Astroid.hpp"
#include "enemies/Disc.hpp"

#include <iostream>

AstroidField::AstroidField() {}

AstroidField::~AstroidField() {}

void AstroidField::loadEnityQueue()
{
    pushEntityToQueue(3.0, std::vector<std::shared_ptr<Entity>>{Game::create<Astroid>(Vector(300, 0))});
    pushEntityToQueue(2.0, std::vector<std::shared_ptr<Entity>>{Game::create<Astroid>(Vector(200, 0))});
    pushEntityToQueue(2.5, std::vector<std::shared_ptr<Entity>>{Game::create<Astroid>(Vector(250, 0))});
    pushEntityToQueue(0.5, std::vector<std::shared_ptr<Entity>>{Game::create<Astroid>(Vector(300, 0)), Game::create<Disc>(Vector(400, 64))});

    pushEntityToQueue(1.0, std::vector<std::shared_ptr<Entity>>{Game::create<Disc>(Vector(400, 64))});

    pushEntityToQueue(3.0, std::vector<std::shared_ptr<Entity>>{Game::create<Astroid>(Vector(500, 0)), Game::create<Astroid>(Vector(600, 0))});
    pushEntityToQueue(1.0, std::vector<std::shared_ptr<Entity>>{Game::create<Astroid>(Vector(400, 0)), Game::create<Disc>(Vector(200, 64)), Game::create<Disc>(Vector(600, 64))});
    pushEntityToQueue(1.0, std::vector<std::shared_ptr<Entity>>{Game::create<Astroid>(Vector(600, 0)), Game::create<Astroid>(Vector(700, 0))});

    pushEntityToQueue(3.0, std::vector<std::shared_ptr<Entity>>{Game::create<Astroid>(Vector(100, 0)), Game::create<Astroid>(Vector(300, 0))});
    pushEntityToQueue(1.0, std::vector<std::shared_ptr<Entity>>{Game::create<Astroid>(Vector(150, 0)), Game::create<Astroid>(Vector(350, 0))});
    pushEntityToQueue(1.0, std::vector<std::shared_ptr<Entity>>{Game::create<Astroid>(Vector(500, 0)), Game::create<Astroid>(Vector(600, 0))});
    pushEntityToQueue(0.5, std::vector<std::shared_ptr<Entity>>{Game::create<Astroid>(Vector(500, 0)), Game::create<Astroid>(Vector(600, 0))});
}

void AstroidField::playBackgroundSound()
{
    Mixer::getInstance()->playSound("backgroundDNB");
}
