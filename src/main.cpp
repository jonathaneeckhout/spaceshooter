#include <iostream>
#include <csignal>
#include <jengine/jengine.hpp>

#include "maps/AstroidField.hpp"
#include "player/Player.hpp"

#include "audio/music/background-drum-and-bass/background-drum-and-bass-117717.h"
#include "fonts/8x8-square-roguelike-ascii-font/8x8-square-roguelike-ascii-font.h"
#include "audio/effects/TheEssentialRetroVideoGameSoundEffectsCollection_ByJuhaniJunkala/Weapons/Lazers/sfx_wpn_laser8.h"
#include "audio/effects/TheEssentialRetroVideoGameSoundEffectsCollection_ByJuhaniJunkala/GeneralSounds/SimpleDamageSounds/sfx_damage_hit1.h"
#include "audio/effects/TheEssentialRetroVideoGameSoundEffectsCollection_ByJuhaniJunkala/GeneralSounds/Impacts/sfx_sounds_impact3.h"
#include "audio/effects/TheEssentialRetroVideoGameSoundEffectsCollection_ByJuhaniJunkala/Weapons/Lazers/sfx_wpn_laser10.h"
#include "audio/effects/TheEssentialRetroVideoGameSoundEffectsCollection_ByJuhaniJunkala/GeneralSounds/Coins/sfx_coin_double1.h"
#include "audio/effects/TheEssentialRetroVideoGameSoundEffectsCollection_ByJuhaniJunkala/Explosions/Short/sfx_exp_short_hard2.h"
#include "audio/effects/TheEssentialRetroVideoGameSoundEffectsCollection_ByJuhaniJunkala/Explosions/MediumLength/sfx_exp_medium5.h"

Game *game = NULL;

static void signalHandler(int signum)
{
    std::cout << "Interrupt signal (" << signum << ") received." << std::endl;

    game->stop();
}

static void loadResources()
{
    Resources *resources = Resources::getInstance();

    // Fonts
    resources->loadResource("defaultFont", __8x8_square_roguelike_ascii_font, __8x8_square_roguelike_ascii_font_len);

    // Audio
    resources->loadResource("backgroundDNB", background_drum_and_bass_117717, background_drum_and_bass_117717_len);
    resources->loadResource("bullet", sfx_wpn_laser8, sfx_wpn_laser8_len);
    resources->loadResource("bulletImpact", sfx_damage_hit1, sfx_damage_hit1_len);
    resources->loadResource("zap", sfx_wpn_laser10, sfx_wpn_laser10_len);
    resources->loadResource("ZapImpact", sfx_sounds_impact3, sfx_sounds_impact3_len);
    resources->loadResource("ZapImpact", sfx_sounds_impact3, sfx_sounds_impact3_len);
    resources->loadResource("powerup", sfx_coin_double1, sfx_coin_double1_len);
    resources->loadResource("explosion0", sfx_exp_short_hard2, sfx_exp_short_hard2_len);
    resources->loadResource("explosion1", sfx_exp_medium5, sfx_exp_medium5_len);
}

static void loadSounds()
{
    auto mixer = Mixer::getInstance();

    mixer->loadSound("backgroundDNB", "backgroundDNB");
    mixer->loadSound("bullet", "bullet");
    mixer->loadSound("bulletImpact", "bulletImpact", 0.8);
    mixer->loadSound("zap", "zap", 0.8);
    mixer->loadSound("ZapImpact", "ZapImpact");
    mixer->loadSound("powerup", "powerup");
    mixer->loadSound("EnemyDestroyedExplosion", "explosion0", 0.7);
    mixer->loadSound("PlayerDestroyedExplosion", "explosion1");
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

    loadSounds();

    loadGame();

    Renderer *renderer = Renderer::getInstance();

    renderer->setWindowTitle("SpaceShooter");

    game->run();

    Game::deleteInstance();

    return 0;
}