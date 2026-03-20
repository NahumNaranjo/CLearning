# HUB - Menu Interface for CLEARNING

HUB is a simple console menu interface written in pure C that lets you launch the available CLEARNING tools.

## Features

- **Menu interface**: Presents a numbered menu in the console.
- **Tool launching**: Starts tools like CXT and CBA.
- **Interactive loop**: Keeps running until you choose to exit.

## Usage

### Run HUB
```bash
./build/hub.exe
```

### Menu Options

1. **Go to CXT** — Launches the CXT text analysis tool.
2. **Go to CBA** — Launches the CBA build helper.
3. **Exit** — Closes the HUB program.

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

- Designed for Windows (console-based).
- Uses the common library for screen operations.
- Part of the CLEARNING ecosystem.

## Version

HUB v1.0.2 - Author: Nahum Naranjo</content>
<parameter name="filePath">d:\Programacion\CLearning\projects\hub\README.md