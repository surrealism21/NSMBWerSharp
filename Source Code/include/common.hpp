#pragma once
#include <kamek.hpp>
#include <nw4r.hpp> // newer shit in here

/* Virtual Function Helpers */
//#define VF_BEGIN(type, obj, id, vtable_offset) \
//	{ type __VFUNC = (((u32)(obj))+(vtable_offset));
#define VF_BEGIN(type, obj, id, vtable_offset) \
	{ type __VFUNC = ((type*)(*((void**)(((u32)(obj))+(vtable_offset)))))[(id)]; // What the fuck?

#define VF_CALL __VFUNC

#define VF_END }

// this is a waste of space but the include system for this codebase is too bad
struct tree_node {
	tree_node *parent, *child, *prev_sibling, *next_sibling;
	void *obj;
};

namespace nw4r { namespace db {
	void Exception_Printf_(const char *msg, ...);
	void* sException();
}}

// Stop the auto completion from whining
#ifdef __CLANG
inline void *operator new(unsigned int size, void *ptr) { return ptr; }
float abs(float value);
double abs(double value);
#endif
#ifndef __CLANG
inline void *operator new(size_t size, void *ptr) { return ptr; } // dare i say best hack ever concocted

inline float abs(float value) {
	return __fabs(value);
}
inline double abs(double value) {
	return __fabs(value);
}
#endif

typedef struct { f32 frame, value, slope; } HermiteKey;
float GetHermiteCurveValue(float current_frame, HermiteKey* keys, unsigned int key_count);

extern void *ArchiveHeap; // PAL 0x8042A72C, NTSC 0x8042A44C
