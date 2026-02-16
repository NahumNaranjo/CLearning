# CXT - Text Analysis Tool

CXT is a simple command-line text analysis tool written in C. It allows users to analyze text files for various statistics such as word frequencies, line counts, and most common words. It also supports saving analysis reports and loading previously saved reports.

**Part of the CLEARNING project** - A collection of C learning projects. See the [main README](../../README.md) for more information about the overall project.

## Features

- **Word Frequency Analysis**: Counts the frequency of each unique word in the text, excluding common stop words.
- **Line Count**: Counts the number of lines in the file.
- **Word Count**: Counts the total number of words in the file.
- **Most Common Word**: Identifies the most frequently occurring word.
- **Stop Words Filtering**: Automatically filters out common English stop words (e.g., "the", "a", "is").
- **Report Saving**: Save analysis results to a timestamped file.
- **Report Loading**: Load and view previously saved analysis reports.
- **Interactive Mode**: User-friendly command-line interface with help and exit options.

## Usage

1. Run the program: `./cxt.exe`
2. Enter the path to the text file you want to analyze (or a saved report file starting with "analysis_report_").
3. Use the following commands in analysis mode:
   - `info -l`: Display number of lines.
   - `info -w`: Display number of words.
   - `info -m`: Display most common word.
   - `info -f`: Display all word frequencies.
   - `info -a`: Display all statistics.
   - `write`: Save the current analysis to a file.
   - `help`: Show help menu.
   - `exit`: Exit analysis mode.
4. Main menu commands:
   - Enter a file path to analyze.
   - `help` or `h`: Show main help.
   - `version` or `v`: Show version information.
   - `exit`: Quit the program.

## Building

Run the CL installer, this dependencie does not have a separate one yet.

## Dependencies

- CMake
- Ninja
- GCC (MinGW on Windows)
- Standard C libraries
- Windows-specific functions (for console operations)

## File Structure

- `main.c`: Main program logic, user interface, and command handling.
- `txtFunctions.c`: Core text analysis functions (word counting, frequency analysis).
- `ui.c`: User interface functions (menus, input handling).
- `readFile.c`: File reading and report parsing utilities.
- `writeFile.c`: Report writing functionality.
- `map.h`: Data structure definitions.
- `txtFunctions.h`: Function declarations for text analysis.
- `ui.h`: UI function declarations.
- `readFile.h`: File handling declarations.
- `writeFile.h`: Report writing declarations.

## Report Files

Analysis results can be saved as report files with timestamps. These files can be loaded back into the program for viewing. Report files are saved in `c:\InCGames\cl\cxt\reports\` (created automatically) and follow the naming convention `analysis_report_HH:MM:SS.txt`.

## Notes

- The tool performs basic text cleaning, removing punctuation and handling quotes.
- Stop words are filtered after text cleaning to ensure accurate exclusion.
- Memory is dynamically allocated for word tracking; ensure sufficient RAM for large files.
- The program is designed for Windows and uses Windows-specific console functions.

## Version

CXT - Text Analyzer v1.0.3