#include <kamek_asm.S>

.extern LoadBreffKoopa
.extern LoadBreffKoopaJr
.extern returnFromBreffLoadPatch

.global BreffLoadPatch

.text
.align 4

kmBranchDef 0x809201EC
BreffLoadPatch:
	# Original instruction
	lhz r0, 0(r27)# get sprite id
	
	cmpwi r0, 493 # ClownCar loads Bowser Jr effects
	beq KoopaJr
	cmpwi r0, 494 # Thunder Cloud will load thunder effect file
	beq KoopaJr
	cmpwi r0, 500 # Electric Line will load thunder effects file
	beq KoopaJr
    cmpwi r0, 523 # Captain Bowser will load bowser effect file
    beq Koopa
	
	# Otherwise keep doing the game's original checks
	b returnFromBreffLoadPatch

Koopa:
	b LoadBreffKoopa

KoopaJr:
	b LoadBreffKoopaJr