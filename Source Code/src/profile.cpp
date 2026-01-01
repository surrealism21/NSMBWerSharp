#include <profile.hpp>
#include <game.hpp>

// Nop instructions
// note: the nops are not in the assembly because i am lazy and like CPP macros
// I did write a asm nop macro (hopefully) though.

//SpriteList_r3_nop
kmWriteNop(0x80068f38);

//SpriteList_r7_nop
kmWriteNop(0x807fc8cc);

//SpriteList_r9_nop
kmWriteNop(0x80068e0c); //changed from 0x80068dfc

//r28
kmWriteNop(0x8085fc6c);

//r29
kmWriteNop(0x8085f68c);

//r30
kmWriteNop(0x80068414);

//r30 TWO!
kmWriteNop(0x8085f804);

//r30 THREE!
kmWriteNop(0x8085fe14);


// SPRITES

SpriteData sprites[SpriteId::Num] = { 0 };

class SpritesSetter {
public:
    SpritesSetter();
};

SpritesSetter::SpritesSetter() {
    for (u32 i = 0; i < 483; i++) {
        sprites[i] = originalSprites[i];
	}
}

static SpritesSetter doSetSprites;

// PROFILES

Profile* profiles[ProfileId::Num] = { 0 };
extern "C" Profile** ObjectProfileList;

class ProfileSetter {
public:
    ProfileSetter();
};

ProfileSetter::ProfileSetter() {
    ObjectProfileList = &profiles[0];

    for (u32 i = 0; i < ORIGINAL_PROFILES; i++) {
        profiles[i] = originalProfiles[i];
    }
}

static ProfileSetter doSetProfiles;

kmBranchDefCpp(0x80768690, NULL, void, void) {
    ObjectProfileList = &profiles[0];
}

// SPRITE FILES

extern "C" const char** spriteFiles[483];
const char** customSpriteFiles[SpriteId::Num - 483] = { 0 };

// PROFILE NAMES

extern "C" const char* profileNames[ORIGINAL_PROFILES];
const char* customProfileNames[ProfileId::Num - ORIGINAL_PROFILES] = { 0 };

kmBranchDefCpp(0x801018c0, NULL, const char*, unsigned int profileId) {
    if (profileId < ORIGINAL_PROFILES) {
        return profileNames[profileId];
    }
    return customProfileNames[profileId - ORIGINAL_PROFILES];
}

// CUSTOM PROFILE CTOR

Profile::Profile(dActor_c* (*buildFunc)(), u32 id, const SpriteData* spriteData, u16 executeOrderProfileId, u16 drawOrderProfileId, const char* name, const char** files, u32 flags) {
    this->buildFunc = buildFunc;
    this->executeOrderProfileId = executeOrderProfileId;
    this->drawOrderProfileId = drawOrderProfileId;
	this->flags = flags;

	u32 profileId;
	if (spriteData) {
		sprites[id] = *spriteData;
		if (id < 483) {
			spriteFiles[id] = files;
		}
		else {
			customSpriteFiles[id - 483] = files;
		}
		profileId = spriteData->profileId;
	}
	else {
		profileId = id;
	}
	
	profiles[profileId] = this;
	if (profileId < ORIGINAL_PROFILES) {
		profileNames[profileId] = name;
	}
	else {
		customProfileNames[profileId - ORIGINAL_PROFILES] = name;
	}
}