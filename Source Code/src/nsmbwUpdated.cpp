#include <kamek.hpp>

// daEnRotarionGhost_c can be killed by a Propeller Suit spin-drill.

// More information on this type of bug can be found in
// nsmbwup_propeller_suit_drillable_actors.h.

kmWrite8(0x80ad415a, 0x88);

// Thanks to Grop for this patch.

// When Mario enters a door, he decides if the door is "wide" or not,
// which affects some details of his animation.

// If Mario isn't "close enough" to the center of a normal door, he'll
// automatically walk to the center before entering it. If he is, the
// walking animation will be skipped, and he'll just slide toward the
// center while walking away from the camera instead.

// Doors considered wide have a slightly larger radius for the "close
// enough to the center" range (5/8 of a tile instead of 1/2), and they
// omit the sliding behavior. (These changes take place in
// dAcPy_c::exeDemoOutDoor_OpenDoor() and
// dAcPy_c::exeDemoOutDoor_MoveInter() respectively.)

// dAcPy_c::setDoorDemo() classifies a door into one of the
// two categories. It considers tower (EN_TORIDEDOOR) and castle
// (EN_CASTLEDOOR) doors wide, and all others normal. It seems, however,
// that the developers forgot to consider the Bowser's Castle boss room
// door, which is the widest door in the game.

// This patch adjusts the condition to include this door in that
// category. Note that both the code being patched and the patch itself
// rely on the fact that these three profile IDs are sequential.

kmWrite32(0x8013f41c, 0x28000002);  // cmplwi r0, 2

// The Bush sprite just uses the default single-tile spawn range instead
// of configuring it to fit the actor's actual shape. This works fine at
// the default "small" size, but with any of the larger size settings,
// this can cause severe pop-in when approached from above.

// We fix this by simply increasing the spawn range vertically. The
// largest bush size is about 4 tiles (aka 64 units) taller than the
// default, so we increase it by that much.

kmWrite32(0x8030dfc8, 64);  // Move spawn range 4 tiles up
kmWrite32(0x8030dfd4, 64);  // Increase spawn range height by 4 tiles

typedef struct NextGoto {
	/* 0x00 */ unsigned short x;
	/* 0x02 */ unsigned short y;
	/* 0x04 */ unsigned short _4;
	/* 0x06 */ unsigned short _6;
	/* 0x08 */ unsigned char id;
	/* 0x09 */ unsigned char dest_area;
	/* 0x0a */ unsigned char dest_id;
	/* 0x0b */ unsigned char type;
	/* 0x0c */ unsigned char _c;
	/* 0x0d */ unsigned char zone_id;
	/* 0x0e */ unsigned char layer;
	/* 0x0f */ unsigned char direct_pipe_path_id;
	/* 0x10 */ unsigned short flags;
    /* 0x12 */ bool leave_stage;
    /* 0x13 */ unsigned char _13;
} NextGoto;

class dCdFile_c {
public:
    NextGoto *getNextGotoP(unsigned char id);
};

// Thanks to Ninji (Treeki) for this patch.

// daPlBase_c::initializeState_DemoRailDokan() is responsible for
// starting a direct-pipes player movement animation. This involves
// initializing a daPlBase_c field unofficially known as
// "nextPathNodeIndex", to either "1" or "path->numNodes - 2" depending
// on the entrance's "direct pipe reversed" flag (which makes the player
// follow the path backward from the end). It also checks that first
// node's position, to set the first target position for the player to
// linearly slide to.

// Unfortunately, though, it performs those two operations in the wrong
// order: it uses a *stale* value of "nextPathNodeIndex" to get the
// pointer to the first path node, before initializing it right after.
// This means the first path node may be anything: usually it's the
// first one in the area (index 0) the first time a player uses a
// direct-pipe entrance, and then some other, often invalid value for
// subsequent direct-pipe traversals. This frequently results in the
// player traveling to their death somewhere outside of the zone
// boundaries.

// To summarize, the function does

//     lvlRailNode *firstNode = area->pathNodesBlock[
//         path->startNodeIndex + this->nextPathNodeIndex];
//     this->nextPathNodeIndex = (destEntrance->flags & 0x0001)
//         ? (path->numNodes - 2) : 1;

// and the order of those two lines needs to be swapped.

// To do this, we simply overwrite that block of code with essentially
// the same assembly instructions, shuffled into the correct order.

// First line (initializing the next-path-node index)
       /* 0x800508f8 */             // lhz r0, 0x10(r30)              // r0 = destEntrance->flags;
kmWrite32(0x800508fc, 0x540007ff);  // clrlwi. r0, r0, 0x1f           // r0 &= 0xff;
kmWrite32(0x80050900, 0x41820014);  // beq NOT_DIRECT_PIPE_END        // if (r0 & DIRECT_PIPE_END) {
kmWrite32(0x80050904, 0xa0e30004);  // lhz r7, 4(r3)                  //     this->nextPathNodeIndex = path->numNodes - 2;
kmWrite32(0x80050908, 0x3807fffe);  // subi r0, r7, 0x2               //
kmWrite32(0x8005090c, 0xb01f042c);  // sth r0, 0x42c(r31)             //
kmWrite32(0x80050910, 0x4800000c);  // b AFTER_DIRECT_PIPE_END_CHECK  // }
                                    // NOT_DIRECT_PIPE_END:           // else {
kmWrite32(0x80050914, 0x38000001);  // li r0, 1                       //     this->nextPathNodeIndex = 1;
kmWrite32(0x80050918, 0xb01f042c);  // sth r0, 0x42c(r31)             //
                                    // AFTER_DIRECT_PIPE_END_CHECK:   // }

// Second line (calculating the first-node pointer)
kmWrite32(0x8005091c, 0xa0a30002);  // lhz r5, 2(r3)                  // r5 = path->startNodeIndex;
kmWrite32(0x80050920, 0xa89f042c);  // lha r4, 0x42c(r31)             // r4 = this->nextPathNodeIndex;
kmWrite32(0x80050924, 0x80c6003c);  // lwz r6, 0x3c(r6)               // r6 = area->pathNodesBlock;
kmWrite32(0x80050928, 0x7c052214);  // add r0, r5, r4                 // r0 = path->startNodeIndex + this->nextPathNodeIndex;
kmWrite32(0x8005092c, 0x54002036);  // slwi r0, r0, 4                 // (left-shift to prepare for indexing)
kmWrite32(0x80050930, 0x7ca60214);  // add r5, r6, r0                 // r5 = area->pathNodesBlock[r0];

// daPlBase_c::setExitRailDokan(), called at the end of direct-pipes
// animations, switches the player to the correct animation state for
// exiting from the end of the pipe. To choose the right state, it needs
// to know what direction the exit pipe faces.

// It does this by checking the entrance's type. Unfortunately, though,
// it uses the wrong entrance for this -- specifically, the one the
// player *entered*, rather than its *destination*.

// We fix this by hooking on the instruction that calls
// dCdFile_c::getNextGotoP() (which gets the pointer to an entrance,
// given its ID) and replacing it with a new function that recreates
// that call and also adds another to get the pointer to *that*
// entrance's destination. This second pointer is then used for the
// type/direction check.

// We ignore the first entrance's destination-area value. While it
// really ought to match the current area ID, there isn't any useful
// behavior we could do if it doesn't.

kmCallDefCpp(0x80050a50, NextGoto*, dCdFile_c *area, unsigned char src_entrance_id) {
    // Original code (gets the entrance the player entered):
    NextGoto *src_ent = area->getNextGotoP(src_entrance_id);
    // New code (gets that entrance's destination):
    return area->getNextGotoP(src_ent->dest_id);
}

// daPlBase_c::setExitRailDokan(), called at the end of direct-pipes
// animations, switches the player to the correct animation state for
// exiting from the end of the pipe. Specifically, it checks the
// destination entrance's (or the *source* entrance's, if bug C01200
// isn't fixed) type value -- which indicates the pipe direction -- and
// sets the player's "demo" (cutscene) state to one of
// daPlBase_c::StateID_DemoInDokanU, D, L, or R.

// But due to what can only be a typo, it uses StateID_DemoInDokanU for
// *both* of the vertical pipe directions, and never uses
// StateID_DemoInDokanD. The state ID names are a bit unintuitive: this
// bug makes the player exit from upward-facing pipes in the downward
// direction.

// We fix this by replacing the instruction that loads the wrong StateID
// address with some code that loads the right one.

// Implementation note: for each game version in isolation, this can be
// done by replacing a single instruction, but since that instruction
// uses an offset from an arbitrary address (in r31) that was calculated
// earlier in the function, this method should be somewhat safer and
// more robust against different builds of the game with different
// memory layouts.

// Implementation note 2: Newer SMBW works around this bug by instead
// encoding "direction of other side" as a new setting in byte 0x13 of
// the NextGoto struct. That byte is never referenced at all in the
// original game, and that fix clearly doesn't match the intent of the
// original code, which checks entrance types. The fix presented here is
// more correct, but may not work with certain levels that expect
// Newer's version.

extern "C" void* StateID_DemoInDokanD__10daPlBase_c;

kmBranchDefAsm(0x80050a88, 0x80050a8c) {
    lis r4, StateID_DemoInDokanD__10daPlBase_c@h
    ori r4, r4, StateID_DemoInDokanD__10daPlBase_c@l
}

// When using camera mode 5 (event-controlled), the game only switches
// camera modes if the new camera-profile struct would have a different
// index from the current one. Otherwise it refuses to switch to the new
// profile, even if its event is activated.

// Unfortunately, it initializes the attribute that keeps track of the
// current camera profile index to 0 instead of -1. So if you try to
// activate the first profile first, it won't work because the game
// incorrectly thinks it's already using that one. You need to switch to
// the second or higher profile first, and only then can the first
// profile be used.

// Reggie works around this issue by inserting a dummy camera profile
// into the first slot, with the event ID set to 0 so it can never be
// activated. But it's still nice to have the bug, and fix, documented.

kmBranchDefAsm(0x80077290, 0x80077294) {
    nofralloc
    li r31, 0xff
    stb r31, 0x20(r6)
    li r31, 0
    blr
};

// Patches for event controllers implemented by the daFlagObj_c class:
// - Zone Enter: sprite 33, profile 64 (AC_FLAGON)
// - "And": sprite 34, profile 65 (AC_4SWICHAND [sic])
// - "Or": sprite 35, profile 66 (AC_4SWICHOR [sic])
// - Random: sprite 36, profile 67 (AC_RANDSWICH [sic])
// - "Chainer": sprite 37, profile 68 (AC_CHNGESWICH [sic])
// - Location Check: sprite 38, profile 69 (AC_IFSWICH [sic])
// - "Multi-Chainer": sprite 39, profile 70 (AC_RNSWICH [sic])


// If a Zone Enter or Chainer is configured to activate a timed event,
// it accidentally cancels P-Switch music if any is playing when the
// time expires.

// More information on this type of bug can be found in
// nsmbwup_timed_events_canceling_p_switch_music.h.

// Zone Enter:
kmWrite32(0x807eb210, 0x39200001);  // li r9, 1
kmWrite32(0x807eb248, 0x39200001);  // li r9, 1
// Chainer:
kmWrite32(0x807ebaa0, 0x39200001);  // li r9, 1
kmWrite32(0x807ebac8, 0x39200001);  // li r9, 1
kmWrite32(0x807ebb28, 0x39200001);  // li r9, 1
kmWrite32(0x807ebb50, 0x39200001);  // li r9, 1

// Patches for Falling Icicle (daEnIcicle_c): sprite 265, profile 339
// (EN_ICICLE).


// This actor has two dCc_c initialization structs, one for each size
// (1x1, 1x2). Two bugfix patches both flip a bit in the third byte of
// the initialization structs' attack bitfields, so since "kmWrite1()"
// doesn't exist, we have to take handle these two patches together.

// C00800:
// The actor can be killed by a Propeller Suit spin-drill.
// More information on this type of bug can be found in
// nsmbwup_propeller_suit_drillable_actors.h.

// C00504:
// The actor can be eaten by Yoshi.
// More information on this type of bug can be found in
// nsmbwup_yoshi_edible_actors.h.

// Note that for C00504, we only patch the attack bitfield if the
// "passthrough" patch option is chosen -- for the "iceball" option, we
// keep that bit set and change the behavior through a completely
// different mechanism (see further below).

// Also note that "passthrough" is the default option, which is why we
// check for it with "!defined(NSMBWUP_C00504_ICEBALL)".

#define FALLING_ICICLE_ATTACK_BITFIELD_BYTE2 0x5f

// Patch it in
kmWrite8(0x80ad0eba, FALLING_ICICLE_ATTACK_BITFIELD_BYTE2);  // for 1x1 size
kmWrite8(0x80ad0ede, FALLING_ICICLE_ATTACK_BITFIELD_BYTE2);  // for 1x2 size

// Patch field 0x36d to 5, causing it to become an iceball when eaten
kmBranchDefAsm(0x80a20b48, 0x80a20b4c) {
    nofralloc
    stfs f0, 0x31c(r28)
    li r4, 5
    stb r4, 0x36d(r28)
    blr
};

// Patches for Giant Floating Log (unknown class name): sprite 173,
// profile 501 (EN_MARUTA).

// The actor can be eaten by Yoshi.

// More information on this type of bug can be found in
// nsmbwup_yoshi_edible_actors.h.

// Patch the attack bitfield
kmWrite8(0x80ad2e5e, 0x5f);

// Patches for Icicle (daEnFixationIcicle_c): sprite 201, profile 511
// (EN_FIXATION_ICICLE).


// This actor has two dCc_c initialization structs, one for each size
// (1x1, 1x2). Two bugfix patches both flip a bit in the third byte of
// the initialization structs' attack bitfields, so since "kmWrite1()"
// doesn't exist, we have to take handle these two patches together.

// C00802:
// The actor can be killed by a Propeller Suit spin-drill.
// More information on this type of bug can be found in
// nsmbwup_propeller_suit_drillable_actors.h.

// C00505:
// The actor can be eaten by Yoshi.
// More information on this type of bug can be found in
// nsmbwup_yoshi_edible_actors.h.

// Note that for C00505, we only patch the attack bitfield if the
// "passthrough" patch option is chosen -- for the "iceball" option, we
// keep that bit set and change the behavior through a completely
// different mechanism (see further below).

// Also note that "passthrough" is the default option, which is why we
// check for it with "!defined(NSMBWUP_C00505_ICEBALL)".

#define ICICLE_ATTACK_BITFIELD_BYTE2 0x5f

// Patch it in
kmWrite8(0x80acfd0e, ICICLE_ATTACK_BITFIELD_BYTE2);  // for 1x1 size
kmWrite8(0x80acfd32, ICICLE_ATTACK_BITFIELD_BYTE2);  // for 1x2 size

// Patch field 0x36d to 5, causing it to become an iceball when eaten
kmBranchDefAsm(0x809fdf70, 0x809fdf74) {
    nofralloc
    stfs f0, 0x31c(r30)
    li r4, 5
    stb r4, 0x36d(r30)
    blr
};

// Patches for Jumbo Ray Respawner 2 (daMantaMgr2_c): profile 526
// (MANTA_MGR2).

// The used Jumbo Ray Respawner actor (MANTA_MGR) has two methods for
// deleting its child Rays:

// * 8085f570 (unofficially, "daMantaMgr_c::deleteAllChildren()")
//   deletes all of them. This is only called when the manager itself is
//   being deleted.
// * 8085f5c0 (unofficially,
//   "daMantaMgr_c::deleteAllChildrenInWaitState()") deletes only those
//   which are in the "Wait" state (not currently flying across the
//   screen). This is called whenever the manager spawns a new set of
//   Rays.

// The unused version, MANTA_MGR2, only has a copy (8085fbe0,
// unofficially "daMantaMgr2_c::deleteAllChildren()") of the first
// method, and calls it in both situations. This means that existing
// Rays disappear whenever the next ones are spawned.

// This is likely a bug, because this actor also has a setting (unique
// to it) to use a different spawn rate when at least one Ray is being
// ridden by a player. That feature wouldn't make sense if the delays
// were intended to be long enough for all Rays to go entirely
// off-screen before the next set could spawn, since that would force
// all players to dismount.

// This can be fixed by redirecting two of the three calls to 8085fbe0
// to daMantaMgr_c's second child-deletion method. Replacing a class
// method with one from a different, non-parent class isn't safe in
// general, but it works in this case because 8085f5c0 only accesses
// fields from the fBase_c class that all actors inherit. This seems
// like a better fix than copying the entire function into this file
// just for the conceptual purity of avoiding code-sharing between the
// two classes.

kmWrite32(0x80860070, 0x4bfff551);  // bl 0x8085f5c0
kmWrite32(0x808600d4, 0x4bfff4ed);  // bl 0x8085f5c0

// Patches for EGG's custom system for dynamically generated lightmaps.

// Thanks to Skawo and Ninji for this patch.

// Dynamically generated lightmap materials are set to nearest-neighbor
// filtering rather than linear, resulting in pixelated-looking
// reflections on models when played in Dolphin with increased internal
// resolution.

// Here, we patch EGG::LightTexture::draw() to force the
// EGG::CpuTexture's minFilter and magFilter fields to 5
// (Linear_Mipmap_Linear) and 1 (Linear) respectively, just before
// they're drawn.

// A better solution would be to patch these values when they're
// initialized in EGG::LightTexture::initialize() (see P1: 802cbe5c).
// Unfortunately, that function runs before the Kamek loader, so that
// doesn't work with the current loader setup.

kmBranchDefAsm(0x802cc5f4, 0x802cc5f8) {
    nofralloc
    li r4, 5
    stb r4, 0xc(r3)
    li r4, 1
    stb r4, 0xd(r3)
    li r4, 0
    blr
};

// Patches for Red Ring (daEnRedRing_c): sprite 156, profile 495
// (EN_REDRING).

// If the actor is configured to activate an event, it accidentally
// cancels P-Switch music if any is playing when the event expires after
// a short time.

// More information on this type of bug can be found in
// nsmbwup_timed_events_canceling_p_switch_music.h.

kmWrite32(0x80a93034, 0x39200001);  // li r9, 1

// Patches for Rotation-Controlled Coin (daEnCoinAngle_c): sprite 253,
// profile 530 (EN_COIN_ANGLE).

// The actor misuses the rotation controller's "starting rotation"
// spritedata field.

// More information on this type of bug can be found in
// nsmbwup_rotation_controlled_actors_starting_rotation.h.

// TODO: This patch breaks the following retail stages:
// - 1-castle: the rotation controllers attached to the gears and coins
//   use a starting angle value of "1".
// - Coin-2: this stage uses lots of intentionally confusing
//   rotation-controlled blocks and coins.
// - 7-2, 8-1, 8-3: the location-triggered bonus coins that rotate in
//   from below the stage use a starting angle value of "4" to mean 180
//   degrees. One structure in 8-3 nonsensically uses starting_angle = 8
//   to mean 0 degrees. (That one should really be redone, since it's
//   the only one where the blocks and coins end up upside-down.)
// The stages should be modified (under this same bug ID) to compensate.

kmWrite32(0x809e55f4, 0x3860c000);  // li r3, -0x4000
kmWrite32(0x809e560c, 0x3860c000);  // li r3, -0x4000

// Patches for Rotation-Controlled Event Deactivation Block
// (daEnObjRotationBlock_c): sprite 252, profile 529
// (EN_ROTATION_BLOCK).

// The actor misuses the rotation controller's "starting rotation"
// spritedata field.

// More information on this type of bug can be found in
// nsmbwup_rotation_controlled_actors_starting_rotation.h.

kmWrite32(0x80a7b558, 0x3860c000);  // li r3, -0x4000
kmWrite32(0x80a7b570, 0x3860c000);  // li r3, -0x4000

// Patches for Rotation-Controlled Blocks (daEnBlockAngle_c):
// - Rotation-Controlled ? Block: sprite 255, profile 532
//   (EN_BLOCK_HATENA_ANGLE)
// - Rotation-Controlled Brick Block: sprite 256, profile 533
//   (EN_BLOCK_RENGA_ANGLE)

// The actor misuses the rotation controller's "starting rotation"
// spritedata field.

// More information on this type of bug can be found in
// nsmbwup_rotation_controlled_actors_starting_rotation.h.

// TODO: This patch breaks the following retail stages:
// - Coin-2: this stage uses lots of intentionally confusing
//   rotation-controlled blocks and coins.
// - 8-3: there's a pair of location-triggered brick blocks at the end
//   of the stage.
// The stages should be modified (under this same bug ID) to compensate.

kmWrite32(0x809c15c4, 0x3860c000);  // li r3, -0x4000
kmWrite32(0x809c15dc, 0x3860c000);  // li r3, -0x4000

// Patches for Special Exit Controller (daNextGotoBlock_c): sprite 179,
// profile 226 (AC_NEXTGOTO_BLOCK).

// The actor can be eaten by Yoshi.

// More information on this type of bug can be found in
// nsmbwup_yoshi_edible_actors.h.

// Patch the attack bitfield
kmWrite8(0x80939b8a, 0x7f);

// Patches for Star Coin (daEnStarCoin_c): sprite 32, profile 61
// (EN_STAR_COIN).

// If the actor is configured to activate a timed event, it accidentally
// cancels P-Switch music if any is playing when the time expires.

// More information on this type of bug can be found in
// nsmbwup_timed_events_canceling_p_switch_music.h.

kmWrite32(0x80aaa488, 0x39200001);  // li r9, 1

// Patches for Switch (daEnHnswich_c):
// - ? Switch: sprite 40, profile 72 (EN_HNSWICH [sic])
// - P Switch: sprite 41, profile 73 (EN_PSWICH [sic])
// - ! Switch: sprite 42, profile 74 (EN_QSWICH [sic])
// - Unused ? Switch: sprite 153, profile 498 (EN_BIG_HNSWICH [sic])
// - Small Bowser Switch: sprite 478, profile 75 (EN_BOSS_KOOPA_SWITCH)
// - Large Bowser Switch: sprite 479, profile 76 (EN_BOSS_KOOPA_BIG_SWITCH)

// The game actively moves upside-down switches left by one unit (1/16
// of a tile) upon spawn. This doesn't appear to serve any useful
// purpose, and just makes them look slightly wrong.

// This behavior can also be found in NSMBDS. If it had some reason to
// exist in that game, it's probably unlikely (but admittedly not
// impossible) that it still does here.

kmWriteNop(0x80a19a7c);

// Patches for Toad House Chest (daStrongBox_c): sprite 203, profile 293
// (AC_STRONGBOX).

// The actor can be eaten by Yoshi.

// More information on this type of bug can be found in
// nsmbwup_yoshi_edible_actors.h.

// Patch the attack bitfield
kmWrite8(0x8093b43e, 0x7f);

// Patches for Unused Rotation-Controlled Solid Platform
// (daEnLiftRotHalf_c): sprite 107, profile 481 (EN_LIFT_ROTATION_HALF).

// The actor misuses the rotation controller's "starting rotation"
// spritedata field.

// More information on this type of bug can be found in
// nsmbwup_rotation_controlled_actors_starting_rotation.h.

kmWrite32(0x80a5d980, 0x38a0c000);  // li r5, -0x4000

// Patches related to the unused Water Current Controller: sprite 243,
// profile 123 (TAG_WATER).

// dAcPy_c::setPenWaterMoveSpeed() is the function that calculates the
// player's movement speed while swimming underwater with the Penguin
// Suit. Although it does make use of the water-current speed value from
// the global dWaterEntryMng_c instance, it does so using the following
// logic (local variable and struct-member names below are unofficial):

//     float some_local_variable = 0.0f;
//
//     if (dWaterEntryMng_c::m_instance->current != 0.0f) {
//         some_local_variable = 8.25f;
//     }

// This causes a rightward water-current force on Penguin Mario, with
// hardcoded strength, whenever there's any current at all, regardless
// of its actual speed or direction as configured in the
// water-current-controller settings.

// It's not clear *why* the function is written this way. It may just be
// a debugging/testing leftover that was never fixed up, since the
// water-current feature itself was ultimately abandoned.

// The corrected code is simply:

//     float some_local_variable = dWaterEntryMng_c::m_instance->current;

// which is done by the patch below.

// Implementation note: I chose to only patch the second byte of the
// instruction at 80131400, in order to change only the destination
// register without overwriting the immediate offset (0x8c0) with
// itself. This is slightly more future-proof in case there are ever any
// future game releases that change the offset.

// Another valid way to implement this patch would be to leave 80131400
// unchanged and replace 80131404 with fmr f0, f5 instead of with nop.

kmWrite8(0x80131401, 0xa3);         // "lfs f0, OFFSET(r3)" -> "lfs f5, OFFSET(r3)"
kmWriteNop(0x80131404);
kmWriteNop(0x80131408);
kmWriteNop(0x8013140c);

//nsmbwup_world_map_hud.cpp & nsmbwup_yoshi.cpp must still be ported