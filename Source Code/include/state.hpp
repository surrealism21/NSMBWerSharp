#pragma once
#include <common.hpp>

struct ObjState {
	s16 area;
	s16 x;
	s16 y;
	s16 value;
};

s16 RestoreObjectState(ObjState *table, s16 area, float objX, float objY);
s32 StoreObjectState(ObjState *table, s16 area, s16 value, float objX, float objY);