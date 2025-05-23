#include <iostream>
#include <csignal>
#include <jengine/jengine.hpp>

#include "maps/AstroidField.hpp"
#include "player/Player.hpp"
#include "fonts/8x8-square-roguelike-ascii-font/8x8square_roguelike_ascii_font.h"

Game *game = NULL;

static void signalHandler(int signum)
{
    std::cout << "Interrupt signal (" << signum << ") received." << std::endl;

    game->stop();
}

static void loadResources()
{
    Resources *resources = Resources::getInstance();

    resources->loadFont("default", __8x8_square_roguelike_ascii_font_ttf, __8x8_square_roguelike_ascii_font_ttf_len);
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

    loadResources();

    loadGame();

    Renderer *renderer = Renderer::getInstance();

    renderer->setWindowTitle("SpaceShooter");

    game->run();

    Game::deleteInstance();

    return 0;
}