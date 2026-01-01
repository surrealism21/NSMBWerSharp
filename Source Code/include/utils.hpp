#pragma once
#include <common.hpp>

const wchar_t* getLevelNumber(int level);
const wchar_t* getWorldNumber(int world);

bool doesWorldExist(int world);

u32 getStartingHouseKind();

extern int lastLevelIDs[];

void WriteUtf8ToTextBox(nw4r::lyt::TextBox *tb, const char *source);

int getUnspentStarCoinCount();
int getStarCoinCount();
void getNewerLevelNumberString(int world, int level, wchar_t *dest);