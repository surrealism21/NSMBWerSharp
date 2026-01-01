#include <kamek_asm.S>

# Add this to the bl hook!
.global StockItemHack
.global StockItemHackR3
.global ItemNamesHack
.global ItemNamesHackR26

# Add these to the symbol map!
.extern SI_Kinoko, SI_Fireflower, SI_Propeller, SI_Iceflower, SI_Penguin, SI_Star

# From loading.S
.extern I_kinoko, I_fireflower, I_iceflower, I_star, I_propeller, I_penguin, I_hammer

.text
kmCallDef 0x80926d34
StockItemHack:
  lis r28, StockItemList@h
  ori r28, r28, StockItemList@l
  blr

kmCallDef 0x80927a6c
StockItemHack2: # copy because i'm scared
lis r28, StockItemList@h
ori r28, r28, StockItemList@l
blr

kmCallDef 0x808d4d5c
StockItemHackR3:
  lis r3, StockItemListR3@h
  ori r3, r3, StockItemListR3@l
  blr

kmCallDef 0x80926C28
ItemNamesHack:
  lis r31, ItemNamesList@h
  ori r31, r31, ItemNamesList@l
  blr

kmCallDef 0x80927918
ItemNamesHackR26:
  lis r26, ItemNamesList@h
  ori r26, r26, ItemNamesList@l
  blr

.data
.align 4
StockItemList:
	.long SI_Kinoko
	.long SI_Fireflower
	.long SI_Propeller
	.long SI_Iceflower
	.long SI_Penguin
	.long SI_Star
	.long SI_hammer

StockItemListR3:
	.long SI_Kinoko
	.long SI_Fireflower
	.long SI_Propeller
	.long SI_Iceflower
	.long SI_Penguin
	.long SI_Kinoko
	.long SI_Star
	.long SI_hammer

ItemNamesList:
	.long teresa
	.long I_kinoko
	.long I_fireflower
	.long I_iceflower
	.long I_star
	.long I_propeller
	.long I_penguin
	.long I_hammer

SI_hammer:
	.string "SI_Hammer"

teresa:
	.string "teresa"