#include <common.hpp>
#include <utils.hpp>
#include <levelinfo.hpp>


int lastLevelIDs[] = {
	-1, /*no world*/
	27, 27, 27, 27, 27, 27, 27, 25,
	10,
	24, 24, 21, 24, 3
};

static const wchar_t *levelNumbers[] = {
	//mariofont
	L"0",
	L"1",
	L"2",
	L"3",
	L"4",
	L"5",
	L"6",
	L"7",
	L"8",
	L"9",
	L"A", //10
	L"B", //11
	L"C", //12
	L"D", //13
	L"E", //14
	L"F", //15
	L".", //16
	L":", //17
	L"!", //18
	L"?", //19
	//picturefont
	L"G", //20, coin
	L"0", //21, ghost house
	L"/", //22, tower
	L"/", //23, tower 2
	L".", //24, castle
	L"=", //25, bowser castle
	L"9", //26, green house
	L"3", //27, red house
	L"8", //28, star house
	L"3", //29, red house
	L"@", //30, ?-block
	L"A", //31, red block
	L"B", //32, outlined block
	L">", //33, ambush
	L">", //34, ambush
	L">", //35, ambush
	L"1", //36, cannon
	L"?", //37, anchor
	L"2", //38, airship
	L"5", //39, up arrow
	L"4", //40, right arrow
	L"7", //41, peach castle
	L"6", //42, dot
};

static const wchar_t *worldNumbers[] = {
	L"0",
	L"1",
	L"2",
	L"3",
	L"4",
	L"5",
	L"6",
	L"7",
	L"8",
	L"9",
	L"A",
	L"B",
	L"C",
	L"D",
	L"E",
	L"F",
};

const wchar_t* getLevelNumber(int level) {
	if ((level >= 39) && (level <= 40)) {
		switch(getStartingHouseKind()) {
			case 0: //arrow
				return levelNumbers[level];
				break;
			case 1: //yellow
			case 4:
				return levelNumbers[28];
				break;
			case 2: //red
			case 5:
				return levelNumbers[29];
				break;
			case 3: //green
			case 6:
				return levelNumbers[26];
				break;
		}
	}
	return levelNumbers[level];
}

const wchar_t* getWorldNumber(int world) {
	return worldNumbers[world];
}

LevelNumber newGetCourseNum(int worldNum, int levelNum) {
	if ((u32)worldNum > 8) {
		return Stage_Invalid;
	}
	if ((u32)levelNum < 12) {
		//does our world exist?
		dLevelInfo_c::entry_s *liWorld = dLevelInfo_c::s_info.searchBySlot(worldNum, 38);
		if (liWorld) {
			//if so, grab the corresponding section
			dLevelInfo_c::section_s *section = dLevelInfo_c::s_info.getSectionByIndex(worldNum);

			//create list of empty slots
			int levelNumList[12];
			for (int i = 0; i < 12; i++) {
				levelNumList[i] = 42;
			}

			//fill the list with our level slots
			int index = 0;
			for (int i = 0; i < section->levelCount; i++) {
				dLevelInfo_c::entry_s *level = &section->levels[i];
				if (level->flags & 2) {
					levelNumList[index] = level->levelSlot;
					index++;
				}
			}
			//return the level number(s)
			return (LevelNumber)levelNumList[levelNum];
		} else {
			return Stage_Invalid;
		}
	}
	return Stage_Invalid;
}

// i think this causes lag but
kmBranchDefCpp(0x800b4f90, NULL, int, int worldNum, int levelNum) { // levelnumber is a enum (aka int)
	return newGetCourseNum(worldNum, levelNum);
}

extern "C" bool isHomeCourseClear(int world); // 800fcb30
extern "C" u8 getStartKinokoKind(); // 800fb460
extern u8 CurrentWorldNumForWorldMap;
u32 getStartingHouseKind() {
	if (!isHomeCourseClear(CurrentWorldNumForWorldMap)) {
		return 0;
	} else {
		return getStartKinokoKind();
	}
}

void getNewerLevelNumberString(int world, int level, wchar_t *dest) {
	static const wchar_t *numberKinds[] = {
		// 0-19 are handled by code
		// To insert a picturefont character:
		// \x0B\x01YY\xZZZZ
		// YY is the character code, ZZZZ is ignored
		L"A", // 20, alternate
		L"\x0B\x0148\xBEEF", // 21, tower
		L"\x0B\x0148\xBEEF" L"2", // 22, tower 2
		L"\x0B\x012E\xBEEF", // 23, castle
		L"\x0B\x012F\xBEEF", // 24, fortress
		L"\x0B\x013D\xBEEF", // 25, final castle
		L"\x0B\x014D\xBEEF", // 26, train
		L"\x0B\x0132\xBEEF", // 27, airship
		L"Palace", // 28, switch palace
		L"\x0B\x0147\xBEEF", // 29, yoshi's house
		L"\x0B\x014E\xBEEF" L"1", // 30, key 1
		L"\x0B\x014E\xBEEF" L"2", // 31, key 2
		L"\x0B\x014E\xBEEF" L"3", // 32, key 3
		L"\x0B\x014E\xBEEF" L"4", // 33, key 4
		L"\x0B\x014E\xBEEF" L"5", // 34, key 5
		L"\x0B\x014E\xBEEF" L"6", // 35, key 6
		L"\x0B\x0138\xBEEF", // 36, music house
		L"\x0B\x0133\xBEEF", // 37, shop
		L"\x0B\x0139\xBEEF", // 38, challenge house
		L"\x0B\x0151\xBEEF", // 39, red switch palace
		L"\x0B\x0152\xBEEF", // 40, blue switch palace
		L"\x0B\x0153\xBEEF", // 41, yellow switch palace
		L"\x0B\x0154\xBEEF", // 42, green switch palace
	};

	dest[0] = (world >= 10) ? (world-10+'A') : (world+'0');
	dest[1] = '-';
	if (level >= 20) {
		wcscpy(&dest[2], numberKinds[level-20]);
	} else if (level >= 10) {
		dest[2] = '1';
		dest[3] = ('0' - 10) + level;
		dest[4] = 0;
	} else {
		dest[2] = '0' + level;
		dest[3] = 0;
	}
}

int getStarCoinCount() {
	SaveBlock *save = GetSaveFile()->GetBlock(-1);
	int coinsEarned = 0;

	for (int w = 0; w < 10; w++) {
		for (int l = 0; l < 42; l++) {
			u32 conds = save->GetLevelCondition(w, l);

			if (conds & COND_COIN1) { coinsEarned++; }
			if (conds & COND_COIN2) { coinsEarned++; }
			if (conds & COND_COIN3) { coinsEarned++; }
		}
	}

	return coinsEarned;
}