#include <game.hpp>
#include <profile.hpp>

// I think these are supposed to make it use nybble 7 for the animation thing
// Why not just move the spritetex value ??? That's what i did
/*
kmWrite16(0x80a56890, 0x54007e78);
kmWrite16(0x80a569fc, 0x54007e78);
kmWrite16(0x80a6a4ac, 0x5400673f);
kmWrite16(0x802EE81C, 0x41C00000);
kmWrite16(0x8042C6BC, 0x45ABE000);
*/

#define shift 12

// 0x80a6a1c0
kmBranchDefCpp(0x80a6a1c0, NULL, void, dEn_c *megaGoomba) {
//void newSpawnGoombaFromMegaGoomba(dEn_c *megaGoomba) {
    Vec childPos = megaGoomba->pos;
    u32 spriteTexValue = megaGoomba->settings >> shift & 0xF;
    u32 backFenceThing = megaGoomba->appearsOnBackFence << 0x10;
    childPos.x += 4.0;
    dStageActor_c::create(ProfileId::EN_KURIBO, backFenceThing | (spriteTexValue << shift) | 4, &childPos, 0, 0);
    childPos.x -= 8.0;
    dStageActor_c::create(ProfileId::EN_KURIBO, backFenceThing | (spriteTexValue << shift) | 0x100004, &childPos, 0, 0);
}

// 0x80a6a260
kmBranchDefCpp(0x80a6a260, NULL, void, dEn_c *megaGoomba) {
//void newSpawnGoombaFromMegaGoomba2(dEn_c *megaGoomba) {
    Vec childPos = megaGoomba->pos;
    u32 spriteTexValue = megaGoomba->settings >> shift & 0xF;
    u32 backFenceThing = megaGoomba->appearsOnBackFence << 0x10;
    childPos.x += 4.0;
    dStageActor_c::create(ProfileId::EN_KURIBO, backFenceThing | (spriteTexValue << shift) | 5, &childPos, 0, 0);
    childPos.x -= 8.0;
    dStageActor_c::create(ProfileId::EN_KURIBO, backFenceThing | (spriteTexValue << shift) | 0x100005, &childPos, 0, 0);
}

// 0x80a5aa60
kmBranchDefCpp(0x80a5aa60, NULL, void, dEn_c *largeGoomba) {
//void newSpawnMegaGoombaFromLargeGoomba(dEn_c *largeGoomba) {
    Vec childPos = largeGoomba->pos;
    u32 spriteTexValue = (largeGoomba->settings >> shift & 0xF);
    u32 backFenceThing = largeGoomba->appearsOnBackFence << 0x10;
    childPos.x += 9.0;
    dStageActor_c::create(ProfileId::EN_MIDDLE_KURIBO, backFenceThing | (spriteTexValue << shift) | 0x10000000, &childPos, 0, 0);
    childPos.x -= 18.0;
    dStageActor_c::create(ProfileId::EN_MIDDLE_KURIBO, backFenceThing | (spriteTexValue << shift) | 0x10100000, &childPos, 0, 0);
}

// 0x80a5aaf0
kmBranchDefCpp(0x80a5aaf0, NULL, void, dEn_c *largeGoomba) {
//void newSpawnGoombaFromLargeGoomba(dEn_c *largeGoomba) {
    Vec childPos[4];
    childPos[0] = (Vec){largeGoomba->pos.x + 8.0, largeGoomba->pos.y + 16.0, largeGoomba->pos.z};
    childPos[1] = (Vec){largeGoomba->pos.x - 8.0, largeGoomba->pos.y + 16.0, largeGoomba->pos.z};
    childPos[2] = (Vec){largeGoomba->pos.x + 8.0, largeGoomba->pos.y, largeGoomba->pos.z};
    childPos[3] = (Vec){largeGoomba->pos.x - 8.0, largeGoomba->pos.y, largeGoomba->pos.z};
    u32 spriteTexValue = largeGoomba->settings >> shift & 0xF;
    u32 backFenceThing = largeGoomba->appearsOnBackFence << 0x10;
    dStageActor_c::create(ProfileId::EN_KURIBO, backFenceThing | (spriteTexValue << shift) | 5, &childPos[0], 0, 0);
    dStageActor_c::create(ProfileId::EN_KURIBO, backFenceThing | (spriteTexValue << shift) | 0x100005, &childPos[1], 0, 0);
    dStageActor_c::create(ProfileId::EN_KURIBO, backFenceThing | (spriteTexValue << shift) | 0x200005, &childPos[2], 0, 0);
    dStageActor_c::create(ProfileId::EN_KURIBO, backFenceThing | (spriteTexValue << shift) | 0x300005, &childPos[3], 0, 0);
}
