#include <iostream>
#include <csignal>
#include <jengine/Game.hpp>
#include <jengine/Controls.hpp>

#include "Player.hpp"

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
    Player *player = new Player(Vector(400.0, 520.0));
    game->addChild(player);
}

static void registerInputs()
{
    Controls *controls = Controls::getInstance();
    if (controls == nullptr)
    {
        return;
    }

    controls->keyPressHandlers.push_back([](std::string key)
                                         { 
        if(key == "Escape") {
            game->stop();
        } });
}

int main()
{
    game = Game::getInstance();

    std::signal(SIGINT, signalHandler);

    loadResources();

    populateGame();

    registerInputs();

    Renderer *renderer = Renderer::getInstance();

    SDL_SetWindowTitle(renderer->window, "Spaceshooter");

    game->run();

    Game::deleteInstance();

    return 0;
}