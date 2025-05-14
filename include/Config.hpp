#pragma once

#include <cstdint>

namespace Config
{
    constexpr uint32_t WorldCollisionLayer = 0x00000001;
    constexpr uint32_t PlayerCollisionLayer = 0x00000010;
    constexpr uint32_t EnemyCollisionLayer = 0x00000100;
    constexpr uint32_t NoCollisionLayer = 0x00000000;
}