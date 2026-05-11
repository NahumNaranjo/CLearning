# CLEARNING Command Reference

This document provides a comprehensive reference for all commands available in the CLEARNING project tools: **CL** (Command-Line Launcher), **HUB** (Menu Interface), **CXT** (Text Analysis Tool), **CBA** (Build helper), and helper packages.

---

## CL - Command-Line Launcher

`cl` is the main entry point for executing CLEARNING tools from the command line.

### Syntax
```bash
cl [options] [command] [args...]
```

### Options

#### `-h, --help`
Displays help information about available commands and options.

**Example:**
```bash
cl --help
```

**Typical Output:**
```
CL - A bunch of tools made with pure C
Usage: cl [options] [tool/hub]
Options:
  -v, --version       Show version information
  -h, --help          Show this help message
  exec, -e            Execute a tool, usage: "cl exec [toolName]" (also works with hub)
```

#### `-v, --version`
Displays the version information of CL or one of the supported tools.

**Examples:**
```bash
cl --version
cl --version cxt
cl --version cba
cl --version cl
```

**Typical Output:**
```
CL (Ecosystem) version 1.3.3. Author: Nahum Naranjo
```

**Tool-specific output examples:**
```
CXT version 1.1.0. Author: Nahum Naranjo
CBA version 1.0.0. Author: Nahum Naranjo
CUI version 1.0.0. Author: Nahum Naranjo
CFM version 1.1.1. Author: Nahum Naranjo
```

### Command: `exec [tool]`
Executes a specific tool (or the HUB) from `cl`.

**Supported tools:**
- `hub` - Launches the HUB menu interface
- `cxt` - Launches the CXT text analysis tool directly
- `cba` - Launches the CBA build helper

**Examples:**
```bash
cl exec hub
cl exec cxt
cl exec cba
```

**Output examples:**
```
Going to the hub...
```
```
Executing CXT...
```
```
Executing CBA...
```

### Passing arguments to tools (advanced)
Some tools accept additional arguments when launched via `cl exec`.

- **CXT** can analyze a file without opening the menu:
  ```bash
  cl exec cxt "C:\path\to\file.txt" info -a
  ```
  Supported `info` flags: `-l`, `-w`, `-m`, `-f`, `-a`.

- **CBA** can run commands directly:
  ```bash
  cl exec cba build
  cl exec cba init
  cl exec cba clean
  ```

#### Shortcut tool execution (legacy)
`cl` also supports a couple of numeric shortcuts:
- `cl exec 1` → launches `cxt.exe`
- `cl exec 2` → launches `cba.exe`

### Command: `calc` / `-c`
A built-in calculator with operator precedence and trigonometric functions.

**Supported operations:**
- Addition: `+`
- Subtraction: `-`
- Multiplication: `*`
- Division: `/`
- Modulo: `%`
- Sine: `s` (respects degree/radian mode)
- Cosine: `c` (respects degree/radian mode)
- Tangent: `t` (respects degree/radian mode)

**Operator precedence (highest to lowest):**
1. Trigonometric functions (`s`, `c`, `t`)
2. Multiplication, Division, Modulo (`*`, `/`, `%`)
3. Addition, Subtraction (`+`, `-`)

**Examples:**
```bash
cl -c "1+1+1"
cl calc "12+12+12.5"
cl calc "10 * 5 - 3"
cl calc "100 / 2 + 5 * 3"
cl calc "s(30) + c(45)"
```

**Output examples:**
```
# cl -c "1+1+1"
Result: 3

# cl calc "12+12+12.5"
Result: 36.500000

# cl calc "10 * 5 - 3"
Result: 47

# cl calc "s(30) + c(45)"
Result: 1.207107
```

**Configuration:**
`cl calc` respects the angle mode set in `\configs\calc.config`:
- `MODE = d` - Degrees (default)
- `MODE = r` - Radians

**Limitations:**
- Does NOT support parentheses `()`, brackets `[]`, or braces `{}`
- Trigonometric functions are unary operators (work with single numbers)
- Maximum 100 tokens per expression

### Command: `install` / `-i`
Installs a supported package from the `common/packages/` directory into the current workspace.

**Supported packages (as of now):**
- `cui`  (Console UI helper)
- `cxt`  (Text analysis tool)
- `cba`  (Build assistant)
- `cfm`  (File manager helper)
- `ariadne`, `hermes` (other helper packages)

**Example:**
```bash
cl install cxt
cl install cui
```

---

## HUB - Menu Interface

HUB provides a simple text menu interface for launching other CLEARNING tools.

### Usage
Run HUB directly:
```bash
./build/hub.exe
```

Or via CL:
```bash
cl exec hub
# or
cl -e hub
```

### Menu Options

1. **Go to CXT**
   - Launches the CXT text analysis tool.
   - Output: `Going to CXT...`

2. **Go to CBA**
   - Launches the CBA build helper.
   - Output: `Going to CBA...`

3. **Exit**
   - Closes the HUB program.
   - Output: `Exiting...`

### Error Handling
If an invalid option is entered, HUB displays an error message and returns to the menu:

**Example:**
```
Invalid option, please try again.
```

---

## InLine - Console Game Engine

InLine is a new console-oriented game engine module in the CLEARNING project. It is built as a static library in `projects/InLine` and includes core support for game configuration, text input, parsing, rendering, dialogs, and runtime error handling.

### Current capabilities
- Loads game metadata from a text-based game root file.
- Reads player input from the console using `inputLogger.c`.
- Parses simple commands and detects verbs via `textParser.c`.
- Handles runtime error codes through `errorHandler.c` and `errorCodes.txt`.
- Includes an example entry point in `projects/InLine/example/main.c`.

### Files and modules
- `projects/InLine/inFile.c` — game configuration loader
- `projects/InLine/errorHandler.c` — error lookup and reporting
- `projects/InLine/inputLogger.c` — console input capture
- `projects/InLine/textParser.c` — command parsing logic
- `projects/InLine/renderer.c` — output renderer (engine support)
- `projects/InLine/dialog.h` / `dialogs.c` — dialog sequences and choices
- `projects/InLine/errorCodes.txt` — configurable error code definitions

### Notes
- InLine is currently integrated into the main build system as `inl_lib`.
- The engine is still under active development; future updates will complete dialog support and command execution.

---

## CXT - Text Analysis Tool

CXT is a text analysis tool that provides word/line counts, frequency statistics, and report generation.

### Running CXT

From the build output:
```bash
./build/cxt.exe
```

From CL:
```bash
cl exec cxt
# or
cl -e cxt
```

From HUB: select option `1`.

### Main Menu (File selection)

After launching CXT, you will see a simple menu:
- `a` → Analyze a file (enter a file path)
- `l` → Load a previously generated report
- `e` → Exit
- `h` → Help

#### Analyze a file (option `a`)
You will be prompted to enter the full path to a text file.

Example:
```
Please, write your address here:
C:\path\to\file.txt
```

#### Load a report (option `l`)
Lists saved report files from the `cxt\reports` folder.
Select a report by number to re-open it.

### Analysis Mode Commands

Once a text is loaded (either from a file or a saved report), you can enter commands:

- `info -l`  → Show line count
- `info -w`  → Show word count
- `info -m`  → Show most common word
- `info -f`  → Show full frequency table
- `info -a`  → Show all available statistics
- `write`    → Save a report to `cxt\reports`
- `help`     → Display the help menu
- `exit`     → Return to the main menu

**Example session:**
```
info -a
write
exit
```

### Report Files

- **Location:** `cxt\reports\`
- **Naming:** `analysis_report_HH:MM:SS.txt`
- **Load:** Use option `l` at the main menu and pick a report number.

### Error Handling

- **File not found:**
  `Error: File 'nonexistent.txt' not found.`
- **Invalid command:**
  `Unknown command. Type 'help' for available commands.`
- **Analysis failure:**
  `Error: Failed to analyze file.`

---

## CBA - Build Helper

CBA is a simple build assistant to generate a `cba.build` file and/or run CMake/Ninja for a project.

### Usage
Run CBA directly:
```bash
./build/cba.exe
```

Or via CL:
```bash
cl exec cba
```

### Commands
- `init`  → Generate a new `cba.build` file with auto-detected settings
- `build` → Generate `CMakeLists.txt` (if missing) and run CMake + Ninja
- `clean` → Remove the `build` folder

**Examples:**
```bash
cba init
cba build
cba clean
```

### Notes
- If `cba.build` is missing, `cba build` will auto-detect the project and generate it.
- `cba init` always regenerates `cba.build` based on the current directory contents.
- The root project build now includes `InLine` as `inl_lib`, as well as `cui_lib` from the standalone CUI sources.

---

## Helper Packages (Optional)

These are additional helper libraries/tools that can be installed via `cl install`.

### CUI - Console UI Helper
A simple UI toolkit for building text-based menus and dialogs.

Install:
```bash
cl install cui
```

**Build note:** The standalone CUI sources are also built as a static library (`cui_lib`) in the main CLEARNING build.

### CFM - File Manager Utility
A small library for listing files/directories and locating files by name.

Install:
```bash
cl install cfm
```

---

## Notes

- All tools are designed for Windows console environments.
- File paths can use backslashes (`\`) or forward slashes (`/`).
- CXT performs basic cleaning (removes punctuation, handles quotes) for analysis.
- Config files are currently read-only (no runtime config UI).
