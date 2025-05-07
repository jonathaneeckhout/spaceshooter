#include <iostream>
#include <csignal>

#include "jengine/Game.hpp"


Game *game = NULL;

static void signalHandler(int signum)
{
    std::cout << "Interrupt signal (" << signum << ") received." << std::endl;

    game->stop();
}

static void loadResources()
{
    // Resources *resources = Resources::getInstance();

}

static void populateGame()
{
}

int main()
{
    game = Game::getInstance();

    std::signal(SIGINT, signalHandler);

    loadResources();

    populateGame();

    Renderer *renderer = Renderer::getInstance();

    SDL_SetWindowTitle(renderer->window, "Spaceshooter");

    game->run();

    Game::deleteInstance();

    return 0;
}