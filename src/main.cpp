#include <iostream>
#include <csignal>
#include <jengine/jengine.hpp>

#include "factories/Maps.hpp"
#include "factories/Menus.hpp"

#include "audio/music/background-drum-and-bass/background-drum-and-bass-117717.h"
#include "audio/music/deep-space-atmosphere/deep-space-atmosphere-217294.h"
#include "fonts/8x8-square-roguelike-ascii-font/8x8-square-roguelike-ascii-font.h"
#include "audio/effects/TheEssentialRetroVideoGameSoundEffectsCollection_ByJuhaniJunkala/Weapons/Lazers/sfx_wpn_laser8.h"
#include "audio/effects/TheEssentialRetroVideoGameSoundEffectsCollection_ByJuhaniJunkala/GeneralSounds/SimpleDamageSounds/sfx_damage_hit1.h"
#include "audio/effects/TheEssentialRetroVideoGameSoundEffectsCollection_ByJuhaniJunkala/GeneralSounds/Impacts/sfx_sounds_impact3.h"
#include "audio/effects/TheEssentialRetroVideoGameSoundEffectsCollection_ByJuhaniJunkala/Weapons/Lazers/sfx_wpn_laser10.h"
#include "audio/effects/TheEssentialRetroVideoGameSoundEffectsCollection_ByJuhaniJunkala/GeneralSounds/Coins/sfx_coin_double1.h"
#include "audio/effects/TheEssentialRetroVideoGameSoundEffectsCollection_ByJuhaniJunkala/Explosions/Short/sfx_exp_short_hard2.h"
#include "audio/effects/TheEssentialRetroVideoGameSoundEffectsCollection_ByJuhaniJunkala/Explosions/MediumLength/sfx_exp_medium5.h"
#include "audio/effects/TheEssentialRetroVideoGameSoundEffectsCollection_ByJuhaniJunkala/GeneralSounds/Buttons/sfx_sounds_button7.h"

Game *game = NULL;

static void signalHandler(int signum)
{
    std::cout << "Interrupt signal (" << signum << ") received." << std::endl;

    game->stop();
}

static void loadResources()
{
    Resources *resources = Game::getInstance()->resources;

    // Fonts
    resources->loadResource("defaultFont", __8x8_square_roguelike_ascii_font, __8x8_square_roguelike_ascii_font_len);

    // Audio
    resources->loadResource("backgroundDeepSpaceAtmosphere", deep_space_atmosphere_217294, deep_space_atmosphere_217294_len);
    resources->loadResource("backgroundDNB", background_drum_and_bass_117717, background_drum_and_bass_117717_len);
    resources->loadResource("bullet", sfx_wpn_laser8, sfx_wpn_laser8_len);
    resources->loadResource("bulletImpact", sfx_damage_hit1, sfx_damage_hit1_len);
    resources->loadResource("zap", sfx_wpn_laser10, sfx_wpn_laser10_len);
    resources->loadResource("ZapImpact", sfx_sounds_impact3, sfx_sounds_impact3_len);
    resources->loadResource("ZapImpact", sfx_sounds_impact3, sfx_sounds_impact3_len);
    resources->loadResource("powerup", sfx_coin_double1, sfx_coin_double1_len);
    resources->loadResource("explosion0", sfx_exp_short_hard2, sfx_exp_short_hard2_len);
    resources->loadResource("explosion1", sfx_exp_medium5, sfx_exp_medium5_len);
    resources->loadResource("button0", sfx_sounds_button7, sfx_sounds_button7_len);
}

static void loadSounds()
{
    auto mixer = Game::getInstance()->mixer;

    mixer->loadSound("backgroundDeepSpaceAtmosphere", "backgroundDeepSpaceAtmosphere");
    mixer->loadSound("backgroundDNB", "backgroundDNB");
    mixer->loadSound("bullet", "bullet");
    mixer->loadSound("bulletImpact", "bulletImpact", 0.8);
    mixer->loadSound("zap", "zap", 0.8);
    mixer->loadSound("ZapImpact", "ZapImpact");
    mixer->loadSound("powerup", "powerup");
    mixer->loadSound("EnemyDestroyedExplosion", "explosion0", 0.7);
    mixer->loadSound("PlayerDestroyedExplosion", "explosion1");
    mixer->loadSound("button0", "button0");
}

static void registerKeyMappings()
{
    auto controls = Game::getInstance()->controls;

    controls->registerKeys("MoveUp", "W");
    controls->registerKeys("MoveDown", "S");
    controls->registerKeys("MoveLeft", "A");
    controls->registerKeys("MoveRight", "D");

    controls->registerKeys("FireWeapon1", "Keypad 1");
    controls->registerKeys("FireWeapon2", "Keypad 2");

    controls->registerKeys("MuteMusic", "M");

    controls->registerKeys("Enter", "Return");
    controls->registerKeys("Quit", "Escape");
}

static void loadGame()
{

    // auto map = spaceshooter::maps::createAstroidField();
    // game->setRootObject(map);

    auto mainMenu = spaceshooter::menus::createMainMenu();
    game->setRootObject(mainMenu);
}

int main()
{
    game = Game::getInstance();

    game->setFPS(60);

    std::signal(SIGINT, signalHandler);

    loadResources();

    loadSounds();

    registerKeyMappings();

    loadGame();

    game->renderer->setWindowTitle("SpaceShooter");

    game->run();

    Game::deleteInstance();

    return 0;
}
