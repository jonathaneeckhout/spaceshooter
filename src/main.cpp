#include <iostream>
#include <csignal>
#include <jengine/jengine.hpp>

#include "maps/AstroidField.hpp"
#include "Player.hpp"

Game *game = NULL;

static void signalHandler(int signum)
{
    std::cout << "Interrupt signal (" << signum << ") received." << std::endl;

    game->stop();
}

static void loadGame()
{
    auto map = Game::create<AstroidField>();
    game->setRootObject(map);
}

int main()
{
    game = Game::getInstance();

    game->setFPS(60);

    std::signal(SIGINT, signalHandler);

    loadGame();

    Renderer *renderer = Renderer::getInstance();

    renderer->setWindowTitle("SpaceShooter");

    game->run();

    Game::deleteInstance();

    return 0;
}