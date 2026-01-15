![NSMBWer#](/Readme/logo.png)

A Kamek 2 port of [NSMBWer+](https://github.com/Developers-Collective/NSMBWerPlus). The goal of this project is to provide a clean and simple base for mods to work upon and off of, as well as being simple to migrate to from other bases like NSMBWer+ and NewerSMBW.

## Why Kamek 2?
Kamek 2 is a significantly improved system (over Kamek 1, which mods like NSMBWer+ and NewerSMBW use) that allows for **simpler hooks, easier and faster building, as well as new features like conditional hooks and patch exit points**.

## This repository is split between two branches:
### `master`:
- Nearly identical in features to base NSMBWer+
- Only updated with bugfixes/documentation, etc.
- **Recommended for in-development mods** that wish to move to NSMBWer#
    - Has a migration guide (in the works) for easy mod porting
### `extras`:
- Includes all of the features from the newest version of `master`
- An ever-growing list of new features
- **Recommended for mods early in development**
    - Migrating to this branch may pose additional conflicts and issues!

## Changes from NewerSMBW:
- Sprite slot expansion, with all Newer sprites being ported to it.
- Crash fixes.
- 2-Castle hardcode fixes from AnotherSMBW.
- Added more effects to effect spawner.
- Support for Yoshi Drums in music slots 200+.
- Load custom music from the default BRSTM folder.
- Fixes from RoadrunnerWMC's NSMBW-Updated project.
- Several vanilla sprites that have their behaviors modified have settings added for compatibility with vanilla levels.
- Unused actors in the original game have been assigned sprite slots.

## Changes from NSMBWer+:
- The codebase has been cleaned up, removing unused and outdated features from beta versions of NewerSMBW and fixing other issues
- UTF-8 now replaces ASCII in most custom code for virtually unlimited custom characters
- More bugfixes for both NewerSMBW's sprites and SpriteTex
    - Challenge house stars no longer simulate tinnitus when collecting a large amount quickly
    - The fake star coin no longer produces odd effects when colliding with it in certain ways
    - The meteor sprite's electricity can no longer be killed
    - SpriteTex settings no longer crash the game or cause issues
- Unused SpriteTex settings on sprites now have working and/or new options for colors
- Code data is now compressed with LZ11, reducing the base code size from 561 kB to 242 kB.

## Building
This mod's build system uses a build script bundled with an XML file. The XML file is cross-platform and should contain all C++ and ASM files for your mod.
> [!NOTE]
> This build system will only rebuild an object if it has been modified. As of right now, this causes issues with adding profiles (you'll need to delete the entire cache and recompile all of the files if you've added/removed a profile). A fix for this is near, though.

### Windows
- Run `#build.bat`, and the script will output to the `build` folder.

### Linux
- **Wine is needed to run the compiler/assembler; if you haven't already installed it, you'll need to do this.**
- Run the `build.sh` bash script.

### MacOS
 - MacOS is not a 100% guarantee for function.

## Known issues/missing features from NewerSMBW, NSMBWer+, and/or NSMBWer#
- The NewerSMBW chestnut sprite crashes the game when opened if set to contain a spiny, and the spiny sprite was not loaded in a level
- The NewerSMBW chestnut sprite can spawn "moonwalking" goombas if set to contain a goomba
- The NewerSMBW bone piece sprite does not have any collision once rotation reaches 90 degrees
- The NewerSMBW player clown car sprite does not work properly, and is currently not recommended for use.
- Most NewerSMBW sprites do not award points on defeat, and/or cannot be frozen/behave weirdly when frozen
- Many Newer sprites are limited due to a lack of dynamic memory allocation
- Yoshi's egg textures are generally quite broken
- PowerupHax (the hammer suit) has not properly been implemented yet
- Some code hacks that require injection earlier than base Kamek are not currently possible.

If you find any more issues or missing features, pull requests are always welcome.

## NSMBWer+ & NSMBWer# Credits (in no specific order)
All links should link to the people/projects involved. If there are any issues, please feel free to open a pull request.
- [Treeki][treeki] - [Kamek][kamek], NVIDIA shield (Chinese) support
- [Ryguy][ryguy] - [NSMBWer+][nsmbwerplus]
- [surrealism][surrealism] - Modifications to Kamek 2, build script improvements, general code assistance
- [Newer Team][newerteam] - [NewerSMBW][newerwii] and its code, models, sound effects, etc.
- [Nin0][nin0] & [NSMLW Team][nsmlw] - Programming assistance, general assistance, numerous bits of code, [original NSMBWer][nsmbwer], SpriteTex/recolors for the Yoshi egg particles
- [Danster64][danster] - [Original NSMBWer][nsmbwer]
- BupCraft, Lurker, Smecko Geck, SupaNES, [King Pixel][kingpixel] & Others - Bug reporting
- [Kirblue][k*rblue] - Bug reporting, logo, code assistance, more
- [CLF78][clf] - [Original NSMBWer][nsmbwer], Korean/Taiwanese support
- Luminyx - Programming assistance
- [RoadrunnerWMC][roadrunner] - Reggie! Next spritedata, [NSMBW-Updated][updated], Korean/Taiwanese support
- G4L - Improved NewerSMBW models 
- [RedStoneMatt, Asu-Chan][two-very-different-people] - Programming assistance, code loader
- [MandyIGuess][mandy] - Code, more
- Anyone mistakenly not mentioned here (sorry!)

[kamek]:
https://github.com/Treeki/Kamek

[nsmbwer]:
https://github.com/Danster64/NSMBWer

[nsmbwerplus]:
https://github.com/Developers-Collective/NSMBWerPlus

[newerwii]:
https://github.com/Newer-Team/NewerSMBW

[updated]:
https://github.com/NSMBW-Community/NSMBW-Updated



[treeki]:
https://github.com/Treeki

[surrealism]:
https://github.com/surrealism21

[danster]:
https://github.com/Danster64

[nin0]:
https://github.com/N-I-N-0

[two-very-different-people]:
https://github.com/RedStoneMatt

[roadrunner]:
https://github.com/RoadrunnerWMC

[clf]:
https://github.com/clf78

[mandy]:
https://github.com/MandyIGuess

[k*rblue]:
https://github.com/kirbluemodding

[kingpixel]:
https://github.com/TheRealKingPixel

[ryguy]:
https://github.com/Ryguy0777



[newerteam]:
https://github.com/Newer-Team

[nsmlw]:
https://github.com/N-I-N-0/New-Super-Mario-Lost-Worlds
