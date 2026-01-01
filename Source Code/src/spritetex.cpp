#include <kamek.hpp>
#include <game.hpp>

////////////////////
// SpriteTex slop //
////////////////////

// i'm pretty sure these work but like not really

// yoshi a
kmWrite32(0x8093DAB4, 0x3F800000);
kmWrite32(0x8093DABC, 0x40000000);
kmWrite32(0x8093DAC4, 0x40400000);

// yoshi b
kmWrite32(0x8093DAD8, 0x00000003);
kmWrite32(0x8093DAE0, 0x00000001);
kmWrite32(0x8093DAE8, 0x00000002);
kmWrite32(0x8093DAF0, 0x00000000);


//TEX_PokeySnowmanRotA
// these are actually nops
// doesn't waste any performance to just write them tho
kmWriteNop(0x80A9F740);

//TEX_PokeySnowmanRotB
kmWriteNop(0x80A9F768);

//BombMouseHole hooks
kmWrite32(0x80ACE51C, 0x00000200);
kmWrite32(0x80ACE528, 0x00000201);
kmWrite32(0x80ACE538, 0x00000200);
kmWrite32(0x80ACE544, 0x00040200);
kmWrite32(0x80ACE550, 0x00040200);
kmWrite32(0x80ACE55C, 0x00040200);

//BomheiCollisionCallback
// i'm pretty sure dCc_c is "Physics" in newer's codebase. If not, i'll find out
extern "C" void BomheiCollisionCallback(Physics* self, Physics* other);
kmWritePointer(0x80ACE5D0, &BomheiCollisionCallback);

//CloudLT_Execute
//add_func_pointer
extern "C" void CloudLT_Execute(void);
kmWritePointer(0x80AE1868, &CloudLT_Execute);

//////////////////////////////////