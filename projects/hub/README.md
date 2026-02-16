# HUB - Menu Interface for CLEARNING

HUB is a simple menu interface written in pure C that provides a graphical (console-based) way to access the different tools available in the CLEARNING ecosystem.

## Features

- **Menu Interface**: Presents a menu of options in the console.
- **Tool Launching**: Allows selecting and executing tools like CXT.
- **Simple Navigation**: Intuitive interface with numbered options.
- **Interactive Loop**: Allows multiple selections without exiting the program.

## Usage

### Run HUB
```bash
./build/hub.exe
```

### Menu Options

1. **Go to CXT**: Launches the CXT text analysis tool.
2. **Exit**: Closes the HUB program.

## Building

HUB is built automatically as part of the main CLEARNING project. See the [main README](../../README.md) for build instructions.

## Dependencies

- **Common Library**: Uses functions from `screenManagment.h` for console handling.
- **System Functions**: Uses `system()` to execute other programs.

## File Structure

- `main.c`: Main entry point.
- `hub.c`: Menu logic and interpreter.
- `hub.h`: Function declarations.
- `ui.c` and `ui.h`: User interface functions.

## Notes

- Designed for Windows with console-specific functions.
- Uses the common library for screen operations.
- Part of the CLEARNING ecosystem to facilitate tool access.

## Version

HUB v1.0.1 - Author: Nahum Naranjo</content>
<parameter name="filePath">d:\Programacion\CLearning\projects\hub\README.md