# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/), and this project adheres to a comnination of [Semantic Versioning](https://semver.org/spec/v2.0.0.html) and [Calendar Versioning](https://calver.org). Using the same principles as SemVer but changing minor updates to weekly (can be exceptions) drops of content.

## [1.0.0] - 2026-02-03

### Added

#### CL (Command-Line Launcher)
- Command-line argument parsing for options and commands
- Version information display (`-v`, `--version`)
- Help menu display (`-h`, `--help`)
- Tool execution capability (`exec hub`, `exec cxt`)
- Error handling for unknown options
- Windows system call integration for launching executables

#### HUB (Menu Interface)
- Interactive console menu system
- Numbered option selection (1: Go to CXT, 2: Exit)
- Console screen clearing between menu displays
- Error handling for invalid menu selections
- Integration with CXT tool launching

#### CXT (Text Analysis Tool)
- Text file analysis with multiple statistics:
  - Line count (`info -l`)
  - Word count (`info -w`)
  - Most common word identification (`info -m`)
  - Complete word frequency analysis (`info -f`)
  - All statistics display (`info -a`)
- Stop word filtering (common English words like "the", "a", "is")
- Text cleaning (punctuation removal, quote handling)
- Report saving functionality with timestamped filenames
- Report loading from saved analysis files
- Interactive command-line interface with help system
- File path input validation
- Memory management for dynamic word tracking
- Windows-specific console operations

#### Common Library
- Map data structure implementation:
  - Key-value storage using void pointers
  - FindKey() function for key index lookup
  - FindValue() function for value index lookup
  - ExistKey() function for key existence check
  - ExistValue() function for value existence check
- Screen management utilities:
  - clearConsole() for console screen clearing
  - Stop() for execution pause with user input
- Static library compilation for shared usage

#### Build System
- CMake-based build configuration (minimum version 3.10)
- Ninja build generator support
- C11 standard compliance
- GCC/MinGW compiler support on Windows
- Automatic header inclusion for common library
- Executable generation in build directory

#### Project Structure
- Modular project organization with common library
- Cross-project dependencies management
- Comprehensive documentation (README files for each component)
- Windows compatibility focus

### Technical Details
- Pure C implementation without external dependencies
- Standard C library usage only
- Windows API integration for console operations
- Dynamic memory allocation for data structures
- File I/O operations for text analysis and report management
- Command-line interface design
- Modular code architecture with separate header files

### Documentation
- Main project README with build and usage instructions
- Component-specific README files (CL, HUB, CXT, Common)
- Feature descriptions and API documentation
- Build system configuration details
- Dependency and compatibility information
- Comprehensive command reference (DOCUMENTATION.md)

### [1.0.1] - 2026-02-05

#### Chages and additions

#### Common Library
- File finder implementation started:
  - For now, due to this being just a pre-realease, its just the functions I need right now.

#### Hotfixes
- Installer missing folders added
- Setup for CBA development implemented

#### Documentation
- Diary added for day by day thoughts during development.
- Roadmap addded for future plans

### [1.1.0] - 2026-02-06
#### Changes and additions
#### Common library
- File finder updated:
  - lookForRootFiles() and ListDirectories() added for easier file management  

#### Added
- **CBA entered beta:**
  - **Auto CMakelists.txt:** CBA automatically detects every folder and for c files, adding them to their own CMakelists and implementing it all into a main CMakelists.txt file.
  - **Library support:** Wanna code your own libraries for your C projects? add them to /common or /libraries and let CBA do the rest.
  - **Default settings:** When CBA can't find a cba.build file it'll use cba.config to make one from scratch, you can't modify it for now, stay tuned for next update ;D  
(For now, it's only compatible with C projects and a specific project structure, check [cba.md](./projects/cba/README.md) for more detailed information.)

#### Technical Details
- CBA **WILL NOT WORK** if you don't have CMake and Ninja versions (min ver in [cba.md](./projects/cba/README.md))  
#### Hotfixes
- Installer missing files added
- Added .config files, useless for the moment.

### [1.1.1] - 2026-02-09
#### Documentation
- Fixed ALL README.md files
- Updated CHANGELOG.md
- Remade [cba.md](./projects/cba/README.md)
- Usual DIARY.md entries  
- Made some hotfixes

### [1.1.2] - 2026-02-10
#### Libraries
- Added rootFilePath()
- Modified lookForRootFiles()

### [1.1.2] - 2026-02-11
#### InnoSetup
- Added cba and cl to path instead of all .exe's
- Added cba in general

#### hotfixes
- Minor bugfixes
- Added CBA to hub

### [1.2.0 BETA] - 2026-02-13
#### Changes
- **CL overhaul**: Implemented half of it, it's not working yet and i don't know why but i gotta realease a weekly drop, for now, it's just a beta and i'll upload the full version tomorrow or so.
- **CBA refactor**: Just as it is, i remade cba from scratch due to logic issues.
- **Documentation**: i updated everything but the new things from this version are still missing so i'll work on them as soon as i can.

## [1.2.0] - 2026-02-16
### Changes
- **CL overhaul**: We're officially out of beta, ALL changes to cl has been added to the main version. Everything's working as supposed to and i'm pretty happy rn
- **CBA Refactorization**: I'm gonna work on this during the week as I make the next tool.
- **Documentation**: All docs have been updated.

### [1.2.1] - 2026-02-17
#### Additions
- **CFM**: Has been added to the ecosystem but is not accesible for the moment, please be patient.

#### Libraries
- **lookForRootFile**: it is now DEPRACTED, please avoid it's usage in new tools until CFM is ready.

### [1.2.2] - 2026-02-19
#### Additions
- **calc.c**: Another cl overhaul thing. It's just a calculator so enjoy it when it's ready.
- **CFM**: lookInRoot(), getListedDirectories(), getRootFilePath(), findFile(), ParseFile() already under testing

### [1.2.3] - 2026-02-20
#### Fixes
- **calc.c**: Rewritten from scratch to really work this time.

### [1.2.4] - 2026-03-03
#### Fixes
- **calc.c**: Rewrote the parser and for loop, it now supports up to a 100 tokens (numbers and operands) instead of 3 calculations as before.
#### Documentation
- **calc.c**: Added corresponding instrucionts to DOCUMENTATION.md

### [1.2.5p1] - 2025-03-05
#### Fixes
- **calc.c**: Rewrote the for loop and divided into three different loops, one for parenthesis, one for trigonometry and another one for the rest of calculations, also, separed the computing from the calc() function, it now is it's own (compute()) and calc() is only used for parsing.  

## [1.3.0] - 2026-03-06
### Additions
- **calc.c**: Complete rewrite with fundamental improvements:
  - Implemented proper operator precedence evaluation using two-stack algorithm
  - Fixed trigonometric functions (especially tangent which was broken)
  - Added CharStack structure for proper char type handling in operator stack
  - Improved memory management - no memory leaks
  - Enhanced tokenization for better expression parsing
  - Support for up to 100 tokens per expression
  
- **CFM**: Is now out and ready to use coming with the following functions:
  - lookInRoot: Looks for files inside the CL folder path in InCGames parent folder
  - getRootFilePath: Returns the CL folder path in InCGames parent folder
  - getListedDirectories: Lists all child directories of a root one
  - findFile: Looks for a file in a root dir and all its child directories using only its name
  - ParseFile: Returns a line by line of given file.

### Technical Details
- Separated CharStack from Stack for type safety
- Implemented evaluateTokens() with proper precedence handling
- Used shunting-yard-inspired algorithm for expression evaluation
- Eliminated unused helper functions (moveArray, create_subarray_copy, etc.)

### Documentation
- DOCUMENTATION.md updated with complete calc command reference
- Added examples for all supported operations
- Added operator precedence table
- Added configuration mode information

### [1.3.1] - 2026-03-06
#### Additions
- **CUI**: An engine to make command line based UI's.
  - createMenu & displayMenu: Create & display a Menu variable to use in your ui.
  - readInput: Best way to ask the user for info, could be a standalone tool.
  - displayTitle: Customize your projects' titles
- **CFM**: A simple file lister in a predetermined or customized filepath.

#### Fixes
- **CXT**: Remade the ui with the new engine, more remakes to come in next updates.

#### Technical Details
- **CFM**: fileList() is only aviable for windows

#### Documentation
- Updated all README's

### [1.3.2p1] - 2026-03-10
#### Updates
- **CL**: Added cl install [tool] command
- **CFM**: Added dirExists() and getCurrentDirectory() functions

#### Technical Details
- Installer should be significantly heavier now.

### [1.3.2] -2026-03-12
- It's just a formality, this version never really existed, it just has to be here for the file to have sense.

### [1.3.3p1] - 2026-03-12
#### Additions & changes
- Added lots of new files to common so i dont have to link all projects.
- cba has been refactorized.

## [1.4.0] - 2026-03-19
### Additions and changes
- **CUI**: An engine to make command line based UI's.
  - createMenu & displayMenu: Create & display a Menu variable to use in your ui.
  - readInput: Best way to ask the user for info, could be a standalone tool.
  - displayTitle: Customize your projects' titles
- **CFM**: Working on it as usual  
  - A simple file lister in a predetermined or customized filepath.
  - Added dirExists() and getCurrentDirectory() functions.
- **CL**: Added cl install [tool] command
- Added lots of new files to common so i dont have to link all projects.
- cba has been refactorized.
- **HUB**:
  - Remade the UI with new sections for tools and games

### Fixes
- **CXT**: Remade the ui with the new engine, more remakes to come in next updates.

### Technical Details
- **CFM**: fileList() is only aviable for windows

### Documentation
- Updated DOCUMENTATION.md.
- Updated all README.md files.
- Amended the versioning system again.
- CHANGELOG.md's format changed a bit, full versions now contain every changed made during it's development instead of only that release's.

### [1.4.1p1] - 2026-03-23
#### Additions
- **InLine & CCManager set up**

### [1.4.1p2] - 2026-03-26
##### Fixes
- **CCM**: It had some problems with pointers and typedefs, it's now fixed and next update (1.4.1) will be released tomorrow.

### [1.4.1] - 2026-03-30
#### Additions
- **CCManager**: It has now been partially finished, the library part is still missing but the user part is now complete.
- **InLine**: It has been set up and added a few functions (still useless).

### [1.4.2] - 2026-03-31
#### Additions
- **CCManager**: It has been completed, i was wrong about the "library" part, user and library were already finished last update, library part was just buggy.
- **InLine**: InFile has been added (and adapted) succesfully to the project and the dialog system set up.

### [1.4.3] - 2026-04-07
#### Additions
- **CList**: Has been added to the ecosystem, it is just as python's list but obviusly simpler, this one only has about 150 lines and is way less polished.

### [1.4.4] - 2026-04-08
#### Additions
- **inFile.c**: Has been completed, next file to be made for InLine is dialog.c
- **CList**: Added destroyList() for easier removal of lists.

#### Fixes
- **CList**: Deleted unused vars in the list struct and solved logic issues.
- **CFM**: Replaced all `\\` with `/` for better compatibility.
- **CL**: install.c is now universal.
- **CCM**: Changed older, less safe, fixed buffer allocations to safer `malloc`'s and `realloc`'s like CList.
- **CMap**: Didn't checked for `char*` comparisons, now it does `sizeof(map[i].value) == sizeof(char*) ? strcmp(map[i].value, value) == 0 : map[i].value == value`.

#### Technical changes
- **CFM**: Finally took over lookForRootFiles.c, please, if you hadn't changed, do it, lookForRootFile.c is now unaviable. 

#### Documentation
- **README's**: Common and CLearning readme's have been updated.

### [1.4.5] - 2026-04-09
#### Additions
- **dialog.c**: Is partially complete, 1.4.6 will have it.
- **errorHandler.c**: has been added.

#### Fixes
- **inFile.c**: Added env variables and fixed the returning value.

### [1.4.6] - 2026-04-10
#### Fixes
- **CFM**: Fixed `ParseFile()` memory handling and removed the duplicate broken implementation in `cfm.c`. Fixed file lookup in `lookInRoot()`, now it searches the hardcoded InCGames folder and falls back to repo/current directory paths.
- **calc.c**: Updated `configs/calc.config` lookup so `cl calc` can load mode configuration again. Corrected config parsing to use the actual line count returned by `ParseFile()` instead of `sizeof(config) / sizeof(char*)`.

#### Notes
- This was causing `cl calc to stop right after` `debug - file`, because the config file was never opening.

- The fix is now stable enough for a small patch release.

### [1.4.7] - 2026-04-20
#### Additions
- **Build**: Root `CMakeLists.txt` now also builds CFM (`cfm_lib`), CCManager (`ccm_lib`), InLine (`inl_lib`), CL (`cl`), hub, CBA, CXT (`cxt_app`), and the standalone CUI sources as static library `cui_lib` so one `cmake --build` covers the main toolchain.

#### Fixes
- **CXT**: Removed duplicate `projects/cxt/map.h` that collided with `common/map.h`. `AnalyzeTextData` now aliases `CommonAnalyzeTextData`; `AnalyzeText()` wraps `commonAnalyzeText()` from `txtFunctions2.c`. Repaired `readFile.c` / `writeFile.c` to use `CxtMap` consistently so the project compiles and links again.
- **Hub**: Renamed `gameInterpreter` to `gamesInterpreter`, added `toolsInterpreter`, fixed `==` vs `=` in `main.c` exit checks, and initialized menu option counts in `ui.c`.
- **CUI (project copy)**: `CMakeLists.txt` builds `cui_lib` instead of a console `.exe` without `main` (fixes `WinMain` link error). `createMenu()` now copies the title string into `menu->title` instead of using a stray comma expression.

#### Documentation
- **CXT README**: File list updated for the shared `common` analysis code and `cxtMap.h`.

### [1.4.8] - 2026-04-30
#### Additions
- **CList**: Added `findAll()` and `findFirst()` along with `CLIST_NULL`.
- **Inline**: Pretty much finished wiht `errorHandler.c`.

#### Technical changes
- **InLine**: You can change the errors in `errorCodes.txt` now, it's located in your cl folder in `C:\InCGames\cl\`

### [1.4.9] - 2026-05-05
#### Fixes
- **CList**: `findAll()` and `findFirst` now also work with strings, they don't support structs yet.

#### Aditions
- **Ariadne**: `vote()`, `SimpleHeuristic()`, `EntropyAnalysis()`, `SafeString()` and `getXChars()` added as part of the string detection system or just as another feature in `getXChar()`'s case.


### Author
- Developed by Nahum Naranjo as a C learning project