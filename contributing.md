# Contribution Guidelines
## Basic Information
This is the main branch. The main branch, at this point, is about finding problems in the game and fixing them. This generally includes:
 - Base game bug fixes
 - Newer code fixes
 - Optimizations
 - Documentation (look further down for more information regarding this)

## Code guidelines
### File structure and file extensions
- C++ files should have the `.cpp` extension.
- Assembly files should have the `.S` extension.
- C++ headers should have the `.hpp` extension.
- Please use the folders for their intended purposes. Avoid putting things like headers in `/src/`.
- When including headers, use `#include <...>` rather than `#include "..."`. This project does not put headers in the same folder as main files, so quotation includes are not needed.
- Use `#pragma once` instead of include guards when needed.
- Try to avoid inline ASM and ASM branches inside C++ files; if needed, making a `.S` file is significantly cleaner and preferred.
### Code
- Please try to keep your code readable. This means:
    - Avoid adding any unnecessary suffixes or prefixes. Simply `d..._c` or `da..._c` are preferred for classes.
    - Keep variables public whenever possible.
    - Try to avoid using anything besides the `if` statement for checking something (i.e. `do {} while ()`).
    - Code that resembles raw Ghidra decompilier output should be avoided unless strictly necessary
- Name constants or externs towards the top of the file. While this isn't entirely required, it's preferred for organization's sake.
- Includes should go at the very top of the file, with the only exception being `#pragma once`, which is preferred to be at the very top regardless of includes.
### Documentation
- **Do not** use raw, cracked symbols.
    - This repo is not a decompilation. As such, it's preferred that you name symbols something memorable and clear for others or future use.
    - Avoid naming any extern functions from the original `FUN_XXXXXXXX`.
    - Avoid partial decompilation of files unless you plan on finishing it later.
- Avoid making radical changes to headers unless you can properly merge them.