#include <kamek_asm.S>

.text
.align 4

.extern world_map_scripts_table
.extern returnToOriginalScriptCode			#0x801016cc

kmBranchDef 0x801016C8
useCustomScripts:
    lis		r4, world_map_scripts_table@h
    ori		r4, r4, world_map_scripts_table@l
	b		returnToOriginalScriptCode