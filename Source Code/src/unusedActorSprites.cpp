#include <game.hpp>
#include <profile.hpp>
#include <kamek.hpp>

// hooks
// Pleb Goomba
kmWrite32(0x8030a6b0, 0x00350000);

// MANTAMGR2
kmWrite32(0x8030cde8, 0x020E0000);

const char* WaterliftFileList [] = {"lift_han_wood", NULL};
extern "C" dActor_c *dWaterLiftBuild();
const SpriteData WaterliftSpawnerSpriteData = { ProfileId::WATER_LIFT, 0, 0, 0 , 0, 0x10, 0x10, 0, 0, 0, 0, 8};
Profile WaterliftSpawnerProfile(&dWaterLiftBuild, SpriteId::WATER_LIFT, &WaterliftSpawnerSpriteData, ProfileId::WATER_LIFT, ProfileId::EN_KERONPA, "WATER_LIFT", WaterliftFileList, 2);