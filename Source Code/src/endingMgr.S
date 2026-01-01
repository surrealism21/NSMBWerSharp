#include <kamek_asm.S>

.text
.align 4

.set sp, 1
.set rtoc, 2

.extern CheckCurrentLevelAndArea
.extern continueToDontThankMP
.extern continueToThank

kmBranchDef 0x80B4A01C
.global DisablePeachThankMP
DisablePeachThankMP:
    stwu sp, -0x80 (sp) #Push stack, make space for 29 registers
    stmw r3, 0x8 (sp)

    li r3, 8
    li r4, 41
    li r5, 1
    bl CheckCurrentLevelAndArea # check for 8-41, area 1
    cmpwi r3, 0

    lmw r3, 0x8 (sp)
    addi sp, sp, 0x80 #Pop stack

    beq notNewerEnding

    b continueToDontThankMP

notNewerEnding:
    cmpwi r5, 1
    b continueToThank

.extern skipDmEscort
.extern setAnimePlayWithAnimID__10daPlBase_cFi

kmBranchDef 0x80B49E80
.global DisablePeachDmEscort
DisablePeachDmEscort:
    stwu sp, -0x80 (sp) #Push stack, make space for 29 registers
    stmw r3, 0x8 (sp)

    li r3, 8
    li r4, 41
    li r5, 1
    bl CheckCurrentLevelAndArea # check for 8-41, area 1
    cmpwi r3, 0

    lmw r3, 0x8 (sp)
    addi sp, sp, 0x80 #Pop stack

    bne dontDmEscort
    bl setAnimePlayWithAnimID__10daPlBase_cFi
    
dontDmEscort:
    b skipDmEscort

