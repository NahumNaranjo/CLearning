# Common - Shared Library for CLEARNING 

Common is a static library written in pure C that provides shared utilities used by multiple projects within the CLEARNING ecosystem.

## Features

- **Map Structure**: Simple key-value map implementation for data storage.
- **Screen Management**: Functions to clear console and pause execution.
- **Static Library**: Compiled as static library for linking with other projects.

## Components

### Map (map.h / map.c)
Provides a simple data structure for maps:
Download [here](https://github.com/NahumNaranjo/CMap).

- `Map`: Structure containing key and value (void pointers).
- `FindKey()`: Searches for the index of a key in the map.
- `FindValue()`: Searches for the index of a value in the map.
- `ExistKey()`: Checks if a key exists.
- `ExistValue()`: Checks if a value exists.

### Hermes (hermes.h)
Functions for console handling:
Download [here](https://github.com/NahumNaranjo/Hermes).

- `clearConsole()`: Clears the console screen.
- `Stop()`: Pauses execution waiting for user input.
- `readLine()`: Retunrs a `char*` to the user's input.
- `StopM()`: Stops the execution until the user presses enter and displays a custom message.
- `clearUntil()`: Waits for the user to press enter and clears.
- `clearConsoleM()`: Clears console and shows a message.

### Ariadne (ariadne.h)
Functions for string managment:
Download [here](https://github.com/NahumNaranjo/Ariadne).

- **cleanBackSlash()**: Will replace all backslashes with normal ones to imrpove your project's compatibility.
- **trimWhitespace()**: Will trim all whitespaces your string has.

## Usage in Other Projects

**WARNING: Most of the libraries can be found in my [profile](https://github.com/NahumNaranjo) as lone, header-only repos.**

To use the common library in a project:

1. **Include in CMakeLists.txt**:
   ```cmake
   target_link_libraries(your_project common)
   ```

2. **Include headers in code**:
   ```c
   #include "map.h"
   #include "screenManagment.h"
   ```

## Building

The library is built automatically as part of the main CLEARNING project. See the [main README](../README.md) for build instructions.

## Dependencies

- **Standard C Libraries**: Uses only the standard library (stdbool.h, stddef.h, stdio.h).

## Notes

- Designed to be lightweight and reusable.
- Uses void pointers for data type flexibility.
- Compatible with C11 standard.

## Version

Common v1.2.0 - Part of CLEARNING</content>
<parameter name="filePath">d:\Programacion\CLearning\common\README.md