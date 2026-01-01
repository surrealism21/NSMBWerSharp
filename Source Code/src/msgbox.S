#include <kamek_asm.S>

.extern gameStop
.global MessageBoxIsShowing

# -if param & 1 /and/ messagebox is on, 
# otherwise, return Global5758 & param

#.global Query5758Replacement
#Query5758Replacement:
kmBranchDef 0x800B3B50
	mr r5, r3					# save param
	lis r4, gameStop@h
	ori r4, r4, gameStop@l
	lwz r0, 0(r4)				# get 5758
	and r3, r0, r3				# AND with param
	andi. r5, r5, 1			# if param & 1 == 0..
	beqlr					# then return
	
	lis r4, MessageBoxIsShowing@h
	ori r4, r4, MessageBoxIsShowing@l
	lwz r4, 0(r4)
	or r3, r3, r4				# otherwise, OR with MessageBoxIsShowing
	blr						# then return


.data
MessageBoxIsShowing:
	.long 0