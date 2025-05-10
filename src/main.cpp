#include <iostream>
#include <csignal>
#include <jengine/jengine.hpp>

#include "SpaceShooter.hpp"
#include "Player.hpp"

Game *game = NULL;

static void signalHandler(int signum)
{
    std::cout << "Interrupt signal (" << signum << ") received." << std::endl;

    game->stop();
}

static void loadGame()
{
    SpaceShooter *spaceShooter = new SpaceShooter();
    game->addChild(spaceShooter);
}

int main()
{
    game = Game::getInstance();

    game->init();

    game->setFPS(60);

    std::signal(SIGINT, signalHandler);

    loadGame();

    game->run();

    game->cleanup();

    Game::deleteInstance();

    return 0;
}