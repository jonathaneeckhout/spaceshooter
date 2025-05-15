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
    auto spaceShooter = std::make_unique<SpaceShooter>();
    game->setRootObject(std::move(spaceShooter));
}

int main()
{
    game = Game::getInstance();

    game->setFPS(60);

    std::signal(SIGINT, signalHandler);

    loadGame();

    game->run();

    Game::deleteInstance();

    return 0;
}