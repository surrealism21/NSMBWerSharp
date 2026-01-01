#pragma once
#include <game.hpp>

class dLevelInfo_c {
public:
	struct header_s {
		u32 magic;
		u32 sectionCount;
		u32 sectionOffsets[1];
	};

	struct entry_s {
		u8 worldSlot;
		u8 levelSlot;
		u8 displayWorld;
		u8 displayLevel;
		u8 nameLength;
		u8 reserved3;
		u16 flags;
		u32 nameOffset;
	};

	struct section_s {
		u32 levelCount;
		entry_s levels[1];
	};

private:
	header_s *data;

public:
	void load(void *buffer);

	entry_s *searchBySlot(int world, int level);
	entry_s *searchByDisplayNum(int world, int level);

	u32 sectionCount() {
		return data->sectionCount;
	}

	section_s *getSectionByIndex(u32 index) {
		return (section_s*)(((char*)data) + data->sectionOffsets[index]);
	}

	const char *getNameForLevel(entry_s *entry) {
		return (const char*)data + entry->nameOffset;
	}

	static dLevelInfo_c s_info;
};

enum LevelNumber {
    Stage_1 = 0,
    Stage_2 = 1,
    Stage_3 = 2,
    Stage_4 = 3,
    Stage_5 = 4,
    Stage_6 = 5,
    Stage_7 = 6,
    Stage_8 = 7,
    Stage_9 = 8,
    Stage_10 = 9,
    Stage_11 = 10,
    Stage_12 = 11,
    Stage_13 = 12,
    Stage_14 = 13,
    Stage_15 = 14,
    Stage_16 = 15,
    Stage_17 = 16,
    Stage_18 = 17,
    Stage_19 = 18,
    Stage_Coin = 19,
    Stage_Ghost = 20,
    Stage_Tower1 = 21,
    Stage_Tower2 = 22,
    Stage_Castle1 = 23,
    Stage_Castle2 = 24,
    Stage_Toad1 = 25,
    Stage_Toad2 = 26,
    Stage_Toad3 = 27,
    Stage_Toad4 = 28,
    Stage_Unk1 = 29,
    Stage_Unk2 = 30,
    Stage_Unk3 = 31,
    Stage_Enemy1 = 32,
    Stage_Enemy2 = 33,
    Stage_Enemy3 = 34,
    Stage_Warp = 35,
    Stage_Unk4 = 36,
    Stage_Doomship = 37,
    Stage_Home = 38,
    Stage_Title = 39,
    Stage_Peach = 40,
    Stage_Staffroll = 41,
    Stage_Invalid = 42,
};