#include <kamek.hpp>

///////////////
// Bug fixes //
///////////////

// 1-1 bg fix
kmWrite32(0x801180AC, 0x38000003);

// remove opening cutscene
kmWriteNop(0x809191c8);
kmWriteNop(0x809191cc);
kmWriteNop(0x809191d0);
kmWriteNop(0x809191d4);
kmWriteNop(0x809191d8);

// disable quick save
kmWriteNop(0x8077AA7C);
kmWriteNop(0x8092FD08);

// HigherBobombTileExplosionRadius
kmWrite16(0x809CB118, 0x2C1C0003);

// MPDeathPauseFix
kmWriteNop(0x8013DA70);

//Fix memory leaks
kmWrite32(0x800E53E0, 0x4E800020);

// PipeFix_NodeCalc
// ...maybe
kmWritePointer(0x800508F8, 0xA01E0010540007FF41820014A0E300043807FFFEB01F042C4800000C38000001B01F042CA0A30002A89F042C80C6003C7C052214540020367CA60214A8850002);

// Various other pipe fixes
kmWrite32(0x80050A5C,0x88030013);
kmWrite32(0x80050A60,0x2C000000);
kmWrite32(0x80050A68,0x2C000001);
kmWrite32(0x80050A70,0x2C000002);
kmWrite32(0x80050A78,0x2C000003);
//kmWrite32(0x80050A88,0x389F065C); // fixed in nsmbwUpdated.cpp

// Tile god layer fix
kmWrite32(0x807E16D0,0x88D2038F);

// EN_BIGPILE
kmWrite32(0x8001F93C,0x48000014);

// Rocky wrench
kmWriteNop(0x808A9448);

// Front crow
kmWrite32(0x80ACF6A0,0x45ABE000);

//BigMet
kmWrite32(0x809B6EF0,0x38600000);
kmWrite32(0x809B6EC0,0x38600000);
kmWrite32(0x809B6EB0,0x38600000);

// Thwomp
kmWriteNop(0x809F5E40);

// Broozer
// originally there were 3 hooks here, probably. Where's #1?
kmWriteNop(0x809EB284);
kmWrite32(0x809EC5B4,0x38600001);

// from nullsub.S
extern "C" void ReturnNone();

// These prevent stars from killing... spikes??? Unclear.
kmWritePointer(0x80AFF4D8, ReturnNone);
kmWritePointer(0x80AFF784, ReturnNone);
kmWritePointer(0x80AFFA30, ReturnNone);
kmWritePointer(0x80AFFCDC, ReturnNone);
kmWritePointer(0x80AFFF88, ReturnNone);
kmWritePointer(0x80B00234, ReturnNone);

// 2-castle hardcode removal
// You can readd this gimmick if you want to use it.
// But, it is generally quite bad for mods, so...
kmWrite32(0x8000D064,0x280000FF);
kmWrite32(0x80079BD0,0x280000FF);
kmWrite32(0x80079F60,0x280000FF);
kmWrite32(0x8007A898,0x280000FF);
kmWrite32(0x80083A80,0x38600000);
kmWrite32(0x800EBDE4,0x280000FF);
kmWrite32(0x80101C60,0x280000FF);
kmWrite32(0x8015530C,0x280000FF);
kmWrite32(0x807B4EA8,0x280000FF);
kmWrite32(0x807B5328,0x280000FF);
kmWrite32(0x80888958,0x280000FF);
kmWrite32(0x80888B78,0x280000FF);

// Nuke bahps
// Kamek does NOT like writing to rodata.
// So yeah, this is pretty broken. Sorry!

//MusicNukeBahpsNormal1
kmWrite32(0x802F6BC8,0x00000000);
kmWrite32(0x802F6BC9,0x00000000);
kmWrite32(0x802F6BCA,0x00000000);
kmWrite32(0x802F6BCB,0x00000000);

//MusicNukeBahpsNormal2
kmWrite32(0x802F6BE0,0x00000000);
kmWrite32(0x802F6BE1,0x00000000);

//MusicNukeBahpsNormal3
kmWrite32(0x802F6C10,0x00000000);
kmWrite32(0x802F6C11,0x00000000);

//"fix original bubble collision"
kmWrite32(0x802f4e80,0x00000000);
kmWrite32(0x802f4e81,0x41800000);
kmWrite32(0x802f4e82,0x41900000);
kmWrite32(0x802f4e83,0x41900000);

// Fix a bug where the giant floating log is layered above sand
kmWrite32(0x80A63698, 0xC07FFF8C);