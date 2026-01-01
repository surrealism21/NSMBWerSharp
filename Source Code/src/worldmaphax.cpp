#include <kamek.hpp>

// 808dfe50 controls the world 1, 2, 3, 4, 5, and 7 ambushes. better to remove them there than to blr their constructor.
// 808e1750 controls most other hardcoded map actors
// 80904120 controls button press cutscene shit
// 80904440 controls what animation plays when entering a level


// the stuff that has been commented out can be re-enabled at will



/////////////////////////
/* Cannon destinations */
/////////////////////////



// W1-Cannon
kmWrite32(0x802F4CF0, 0x00000004); // world num - 1
// W2-Cannon
kmWrite32(0x802F4CF4, 0x00000004); // same applies here, and for the rest as well
// W3-Cannon
kmWrite32(0x802F4CF8, 0x00000005);
// W4-Cannon
kmWrite32(0x802F4CFC, 0x00000005);
// W5-Cannon
kmWrite32(0x802F4D00, 0x00000007);
// W6-Cannon
kmWrite32(0x802F4D04, 0x00000007);

// yes, this is data from the vanilla game. worlds 7, 8, 9, and 10/A all have their destination value set to A, which is world 11/B
// obviously this map doesn't exist and isn't even supported by the save file, but feel free to change what world it goes to

// W7-Cannon
kmWrite32(0x802F4D08, 0x0000000A);
// W8-Cannon
kmWrite32(0x802F4D0C, 0x0000000A);
// W9-Cannon
kmWrite32(0x802F4D10, 0x0000000A);
// WA-Cannon
kmWrite32(0x802F4D14, 0x0000000A);



/////////////////////////////
/* Level hardcode removals */
/////////////////////////////

// disableLevelRegularCondSetting
kmWriteNop(0x80928448);
// disableLevelNormalCondSetting
kmWriteNop(0x809286BC);
// disableLevelSecretCondSetting
kmWriteNop(0x809286E4);



/////////////////////
/* Ambush removals */
/////////////////////



// removes W1's ambush (goomba)
/*kmWriteNop(0x808DFE70);
kmWriteNop(0x808DFE74);*/

// removes W2's ambush (antlion nests/sand pits)
// kmWriteNop(0x808E0130);

// removes W3's ambush (ice bros)
/*kmWriteNop(0x808DFE88);
kmWriteNop(0x808DFE8c);*/

// removes W4's ambush (porcupuffer)
/*kmWriteNop(0x808DFE78);
kmWriteNop(0x808DFE7C);*/

// removes W5's ambush (stalking piranha plant)
/*kmWriteNop(0x808DFE80);
kmWriteNop(0x808DFE84);*/

// removes W6's ambush (bullet bill)
//kmWrite32(0x808D5210, 0x4E800020);

// removes W7's ambush (lakitu)
/*kmWriteNop(0x808DFE90);
kmWriteNop(0x808DFE94);*/

// removes W8's ambush (lava bubbles/podoboos)
//kmWrite32(0x808CA570, 0x4E800020);



/////////////////////
/* Effect removals */
/////////////////////



// removes W3's falling snow
/*kmWriteNop(0x80321978);
kmWriteNop(0x80321988);*/

// removes W5's poison bubbles
//kmWriteNop(0x803219cc);

// removes W8's lava effects
/*kmWriteNop(0x80321998);
kmWriteNop(0x803219A8);*/

// removes W8's flames in front of bowser's castle
//kmWriteNop(0x80321AA4);

// removes W9's falling comets
//kmWriteNop(0x803219E0);



////////////////////////////////
/* Koopaling/Airship removals */
////////////////////////////////



// removes airships
//kmWrite32(0x808DBEE0, 0x4E800020);

// removes koopalings (must be used with the above patch to prevent errors)
//kmWrite32(0x808F7100, 0x4E800020);



////////////////////////////
/* Miscellaneous removals */
////////////////////////////



// removes the item menu
//kmWriteNop(0x80904298);

// removes the world select
//kmWriteNop(0x809042E4);

// removes the map view
//kmWriteNop(0x809041E8);

// removes the white (surrender) flag that appears when:

// a tower is cleared
//kmWriteNop(0x808F2C68);

// a castle is cleared
//kmWriteNop(0x808CD044);

// bowser's castle is cleared
//kmWriteNop(0x808FF348);

// removes the boo that hovers around the ghost model on the world map
//kmWriteNop(0x808D1494);

// removes the palm trees for:

// W2
/*kmWriteNop(0x808E1C70);
kmWriteNop(0x808E1C74);*/
// W4
/*kmWriteNop(0x808E1C78);
kmWriteNop(0x808E1C7C);*/

// removes the wiggler in W5
//kmWriteNop(0x808E1D38);

// removes the vines that block paths in W5
//kmWriteNop(0x808E1D88);

// removes the giant cloud model from W6
//kmWriteNop(0x808E1DA4);

// removes the clouds from W7
/*kmWriteNop(0x808E1CF4);
kmWriteNop(0x808E1D10);*/

// removes the vine from W7
//kmWriteNop(0x808E1CD0);



///////////////////////////////////////////////////////////////////////////
/* Core patches (don't mess with this unless you know what you're doing) */
///////////////////////////////////////////////////////////////////////////

// expands the map heap
kmWrite32(0x808DF15C, 0x3C800004);