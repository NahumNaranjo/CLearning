# CLEARNING Command Reference

This document provides a comprehensive reference for all commands available in the CLEARNING project tools: CL (Command-Line Launcher), HUB (Menu Interface), and CXT (Text Analysis Tool).

## CL - Command-Line Launcher

CL is the main entry point for executing CLEARNING tools from the command line.

### Syntax
```bash
cl [options] [command]
```

### Options

#### `-h, --help`
Displays help information about available commands and options.

**Example:**
```bash
cl --help
```

**Output:**
```
CL - A bunch of tools made with pure C
Usage: cl [options] [tool/hub]
Options:
  -v, --version       Show version information
  -h, --help          Show this help message
  exec, -e            Execute a tool, usage: "cl exec [toolName]" (also works with hub)
```

#### `-v, --version`
Displays the version information of CL.

**Example:**
```bash
cl --version
```

**Output:**
```
CL version 1.0.0. Author: Nahum Naranjo
```

### Commands

#### `exec [tool]`
Executes a specific tool or navigates to a hub.

**Supported tools:**
- `hub` - Launches the HUB menu interface
- `cxt` - Launches the CXT text analysis tool directly

**Examples:**
```bash
cl exec hub
cl exec cxt
```

**Output for `cl exec hub`:**
```
Going to the hub...
```

**Output for `cl exec cxt`:**
```
Executing CXT...
```

### Error Handling
If an unknown option is provided, CL displays an error message and suggests using help:

**Example:**
```bash
cl --unknown
```

**Output:**
```
Unknown option: --unknown
Use -h or --help for usage information.
```

### `-c, calc [expression]`
A built-in calculator with operator precedence and trigonometric functions

**Supported Operations**
- Addition: `+`
- Subtraction: `-`
- Multiplication: `*`
- Division: `/`
- Modulo: `%`
- Sine: `s` (respects degree/radian mode)
- Cosine: `c` (respects degree/radian mode)
- Tangent: `t` (respects degree/radian mode)

**Operator Precedence** (highest to lowest)
1. Trigonometric functions (`s`, `c`, `t`)
2. Multiplication, Division, Modulo (`*`, `/`, `%`)
3. Addition, Subtraction (`+`, `-`)

**Supported Syntax (Valid expressions)**
- "1 + 1 * 2 / 3.4"
- "1+2*3-4/5"
- "100 % 3 + 2"
- "s(30)" (sine of 30 degrees)
- "c(45) + s(60)" (cosine of 45 plus sine of 60)

**Examples**
```bash
cl -c "1+1+1"
cl calc "12+12+12.5"
cl calc "10 * 5 - 3"
cl calc "100 / 2 + 5 * 3"
cl calc "s(30) + c(45)"
```

**Output Examples**
```bash
# cl -c "1+1+1"
Result: 3

# cl calc "12+12+12.5"
Result: 36.500000

# cl calc "10 * 5 - 3"
Result: 47

# cl calc "s(30) + c(45)"
Result: 1.207107
```

**Configuration**
The calculator respects the angle mode set in `\configs\calc.config`:
- `MODE = d` - Degrees (default)
- `MODE = r` - Radians

**Features**
- Proper operator precedence evaluation
- Up to 100 tokens (numbers and operators) per expression
- Automatic floating-point and integer result formatting
- Support for decimal numbers

### Error Handling
If an invalid expression is used, it will display error messages such as:
```
Error: No expression provided
Usage: calc "3 + 4" or calc 3+4
```
```
Error: Invalid expression
```
```
Error: Invalid operation
```

### Limitations
- Does NOT support parentheses `()`, brackets `[]`, or braces `{}`
- Trigonometric functions are unary operators (work with single numbers)
- Maximum 100 tokens per expression

## HUB - Menu Interface

HUB provides a graphical menu interface in the console for accessing CLEARNING tools.

### Usage
Run HUB directly:
```bash
./build/hub.exe
```

Or:
```bash
  cl exec hub
  # Or
  cl -e hub
```

### Menu Options

#### Option 1: Go to CXT
Launches the CXT text analysis tool.

**Selection:** Enter `1` at the menu prompt.

**Output:**
```
Going to CXT...
```

#### Option 3: Exit
Launches the CBA build helper.

**Selection:** Enter `2` at the menu prompt.

**Output:**
```
Going to CBA...
```

#### Option 3: Exit
Closes the HUB program.

**Selection:** Enter `3` at the menu prompt.

**Output:**
```
Exiting...
```

### Error Handling
If an invalid option is entered, HUB displays an error message and returns to the menu:

**Example:** Enter `3` or any invalid input.

**Output:**
```
Invalid option, please try again.
```
### Direct command execution
CL has a native all in command interpreter, you can write:
```bash
  cl exec [tool] [instruction]
```

For example, to read a file, analyze it and return the info summary with cxt:
```bash
  cl exec cxt path info -a ## will return the same as executing it with cxt
  cl exec cxt path write   ## Will return the report's path
```

## CXT - Text Analysis Tool

CXT is a comprehensive text analysis tool that provides various statistics about text files.

### Usage
Run CXT directly:
```bash
./build/cxt.exe
```
Or use: 
```bash
  cl exec cxt
  # Or
  cl -e cxt

  # Or, if you're in the HUB, use:
  1
  # And that's it
```

### Main Menu Commands

#### File Path Input
Enter the path to a text file to analyze, or a saved report file (starting with "analysis_report_").

**Example:**
```
Enter file path: test.txt
```

**For saved reports:**
```
Enter file path: analysis_report_14:30:45.txt
```

#### `help`
Displays the main help menu.

**Output:**
```
CXT - Text Analyzer v1.0.0
Commands:
  Enter a file path to analyze.
  help or h: Show this help.
  version or v: Show version information.
  exit: Quit the program.
```

#### `version` or `v`
Displays version information.

**Output:**
```
CXT - Text Analyzer v1.0.0
```

#### `exit`
Quits the CXT program.

**Output:**
```
Exiting CXT...
```

### Analysis Mode Commands

After loading a file, CXT enters analysis mode with the following commands:

#### `info -l`
Displays the number of lines in the analyzed file.

**Example:**
```
analysis> info -l
Lines: 42
```

#### `info -w`
Displays the total number of words in the analyzed file.

**Example:**
```
analysis> info -w
Words: 256
```

#### `info -m`
Displays the most frequently occurring word (excluding stop words).

**Example:**
```
analysis> info -m
Most common word: computer (appears 12 times)
```

#### `info -f`
Displays all word frequencies (word and count pairs).

**Example:**
```
analysis> info -f
computer: 12
programming: 8
language: 6
...
```

#### `info -a`
Displays all available statistics (lines, words, most common word, and frequencies).

**Example:**
```
analysis> info -a
Lines: 42
Words: 256
Most common word: computer (appears 12 times)
Frequencies:
computer: 12
programming: 8
...
```

#### `write`
Saves the current analysis results to a timestamped file.

**Output:**
```
Report saved to: c:\InCGames\cl\cxt\reports\analysis_report_HH:MM:SS.txt
```

#### `help`
Displays the analysis mode help menu.

**Output:**
```
Analysis Commands:
  info -l: Display number of lines.
  info -w: Display number of words.
  info -m: Display most common word.
  info -f: Display all word frequencies.
  info -a: Display all statistics.
  write: Save the current analysis to a file.
  help: Show this help menu.
  exit: Exit analysis mode.
```

#### `exit`
Exits analysis mode and returns to the main menu.

**Output:**
```
Exiting analysis mode...
```

## Stop Words

CXT automatically filters out common English stop words during frequency analysis:
- the, a, an, and, or, but, in, on, at, to, for, of, with, by, is, are, was, were, be, been, have, has, had, do, does, did, will, would, could, should, may, might, must, can, shall

## Report Files

- **Location:** Reports are saved to `c:\InCGames\cl\cxt\reports\` (created automatically)
- **Naming:** `analysis_report_HH:MM:SS.txt` (timestamped)
- **Loading:** Can be loaded by entering the report filename in the main menu

## Error Handling

### File Not Found
If the specified file doesn't exist:
```
Error: File 'nonexistent.txt' not found.
```

### Invalid Commands
Unknown commands display:
```
Unknown command. Type 'help' for available commands.
```

### Analysis Errors
If analysis fails:
```
Error: Failed to analyze file.
```

## Examples

### Complete CL Workflow
```bash
# Show help
cl --help

# Execute HUB
cl exec hub

# In HUB menu, select 1 for CXT
1

# In CXT, analyze a file
Enter file path: sample.txt

# Get statistics
analysis> info -a

# Save report
analysis> write

# Exit analysis
analysis> exit

# Exit CXT
exit
```

### Direct CXT Usage (TODO)
```bash
# Run CXT directly
./build/cxt.exe

# Load and analyze
Enter file path: mydocument.txt
analysis> info -l
analysis> info -w
analysis> info -m
analysis> write
analysis> exit
exit
```

## CBA - Auto build helper
CBA writes and does everythin you need to build your C project, I know it's a headache sometimes

### Usage
Same as others, you can access it via HUB, direct path or cl command line.

### Commands
**Build**  
When you're in the root file of your project and executing CBA, run:
```bash
  build
```
**Output**  
if you don't have a cba.build file, it'll return:
```bash
  Error: Could not open build file.
  Current working directory: (current directory)
  Do you want to run "prepare" command? [Y] [N]
  # If yes
  Y
  Preparing build environment...
  Build environment prepared.
  # If not
  N
  Exiting...
```
However, if you do have a proper cba.build file, it'll just build the project

**Preapare**  
When you're in your project's root folder and executing cba, run:
```bash
  prepare
``` 
It'll generate tons of CMakelists.txt and a cba.build file

**Help (TODO)**  

**Exit**
Exits the program.
```bash
  exit
``` 

**Output**
```
  Exiting...
``` 

### Recommended (Supported) project structures
First of all, **CBA will ignore any folders with the following names:**  
"build", ".git", ".vscode", ".github", ".idea", "configs", "docs", "tests", ".cbaignore", "public"  
You can put everything you need there.

**1. ```/Common``` libraries**
```
├── src/                  # Source files (only .c and .h supported, will  
|                         # generate a CMakeLists.txt for this one too)
├── public/               # Public assets
├── test/                 # Automated tests
├── common/               # All your libraries (alternatively libraries)
├── cba.build             # Will be automatically generated
└── CMakelists.cxt        # Will be automatically generated
```

### Examples
### Complete CL Workflow
```bash
# Show help
cl --help

# Execute HUB
cl exec hub

# In HUB menu, select 2 for CBA
2

# In CBA
# Generate a cba.build file based on your configs
prepare

# Build your project
build

# Exit CBA
exit
```

## Notes

- All tools are designed for Windows console environment
- File paths should use Windows format (backslashes or forward slashes)
- Text analysis performs basic cleaning (removes punctuation, handles quotes)
- Memory usage scales with file size for word frequency tracking
- Reports can be reloaded for viewing without re-analysis
- Configs are not modfiable for the moment
- CBA is in still in early development, please be patient