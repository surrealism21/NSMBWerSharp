#include <common.hpp>
#include <game.hpp>
#include <fileload.hpp>

// frame heap patch
kmWrite32(0x80087544, 0x38801000);

struct AnimDef_Header {
	u32 magic;
	u32 entryCount;
};

struct AnimDef_Entry {
	u16 texNameOffset;
	u16 frameDelayOffset;
	u16 tileNum;
	u8 tilesetNum;
	u8 reverse;
};

FileHandle fh;

kmCallDefCpp(0x80087698, void, void* self) {
	OSReport("Trying to load AnimTiles.bin\n");
	AnimDef_Header *header;
	
	header = (AnimDef_Header*)LoadFile(&fh, "/AnimTiles.bin");
	
	if (!header) {
		OSReport("Failed to load AnimTiles.bin.\n");
		return;
	}
	
	if (header->magic != 'NWRa') {
		OSReport("Failed to load AnimTiles.bin: Header magic incorrect.\n");
		FreeFile(&fh);
		return;
	}

	
	AnimDef_Entry *entries = (AnimDef_Entry*)(header+1);
	
	for (int i = 0; i < header->entryCount; i++) {
		AnimDef_Entry *entry = &entries[i];
		char *name = (char*)fh.filePtr+entry->texNameOffset;
		char *frameDelays = (char*)fh.filePtr+entry->frameDelayOffset;
		
		char realName[0x40];
		snprintf(realName, 0x40, "BG_tex/%s", name);
		
		void *blah = BgTexMng__LoadAnimTile(self, entry->tilesetNum, entry->tileNum, realName, frameDelays, entry->reverse);
	}

	OSReport("Successfully loaded AnimTiles.bin. Header: [%p] Entries: [%p].\n", header, entries);
}


kmBranchDefCpp(0x80087508, NULL, void, void* self) {
	FreeFile(&fh);
}


extern "C" void CopyAnimTile(u8 *target, int tileNum, u8 *source, int frameNum) {
	int tileRow = tileNum >> 5; // divided by 32
	int tileColumn = tileNum & 31; // modulus by 32

	u8 *baseRow = target + (tileRow * 2 * 32 * 1024);
	u8 *baseTile = baseRow + (tileColumn * 32 * 4 * 2);

	u8 *sourceRow = source + (frameNum * 2 * 32 * 32);

	for (int i = 0; i < 8; i++) {
		memcpy(baseTile, sourceRow, 32*4*2);
		baseTile += (2 * 4 * 1024);
		sourceRow += (2 * 32 * 4);
	}
}
