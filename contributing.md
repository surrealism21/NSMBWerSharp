# "I've suddenly gained an affinity for the pound sign and wish to contribute!"
## This is the main branch
 The main branch, at this point, is about finding problems in the game and fixing them! This generally includes:
 - Base game bug fixes
 - Newer code fixes
 - Optimizations
 - Documentation (be careful with this one, see its' section)

## Code guidelines
### Files
- C++ files are `.cpp`, and assembly files are `.S`.
- Please use the folders for their intended purposes.

### Headers
- Please use `.hpp` files for headers, this is a C++ project.
- When including headers, use `#include <...>` please.
- Use `#pragma once` rather than include guards, they are ugly.

- Please avoid inline ASM and ASM branches inside C++ files, assembly files exist for a reason!
- If applicable, 

### Code
- Please try to keep your code readable. This means:
    - Do NOT add any unnecessary suffixes or prefixes. The only currently accepted suffix / prefix pair is `d..._c` for classes.
    - Make your variables public, this isn't a megacorp
    - Use the `if` statement for checking something, and no more.
    - Don't use `do {} while ()`!
    - Code that resembles raw Ghidra decompilier output should be avoided unless nessacry (We're talking about those messes of parenthesis and pointers!)
- Try to name any constants or externs near the top of the file. This is not a strict requirement, but...
- You have to name your includes at the top! If you physically can't, the code is probably to hacky anyway.


### Documentation
- Raw cracked symbols are ugly, this is a known fact.
    - This repo is not a decompilation, so you don't need to get them right. Choose a ergonomic name, please, we're trying to **use** this code too!
    - Yes, this means removing those suffixes and prefixes we know all too well.
    - Don't name any extern functions from the original `FUN_XXXXXXXX`. If you're using a function, you should know what it does!
    - Don't decompile a function unless you want to change the whole thing. NSMBW-Decomp is [that way](https://github.com/NSMBW-Community/NSMBW-Decomp).
- If you're going to rename a existing symbol, please insure it works before pulling. Newer's codebase is... unsanitary.
- Avoid making radical changes to headers as the folks at Extra Features may want this sauce as well
