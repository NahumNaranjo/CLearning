# CL - Command-Line Tool Launcher

CL is a simple command-line tool written in pure C that acts as a launcher to execute different utilities and projects within the CLEARNING ecosystem.

## Features

- **Tool Launching**: Allows executing tools like HUB and CXT from the command line.
- **Version Information**: Displays program version information.
- **Built-in Help**: Provides a help menu with available options.
- **Simple Interface**: Minimalist design focused on functionality.

## Usage

### Basic Syntax
```bash
cl [options] [command]
```

### Available Options

- `-v, --version`: Shows version information.
- `-h, --help`: Shows the help menu.
- `exec, -e [tool]`: Executes a specific tool or command.

### Usage Examples

1. **Show help**:
   ```bash
   cl --help
   ```

2. **Show version**:
   ```bash
   cl --version
   ```

3. **Execute HUB**:
   ```bash
   cl exec hub
   ```

4. **Execute CXT**:
   ```bash
   cl -e cxt
   ```

## Building

CL is built automatically as part of the main CLEARNING project. See the [main README](../../README.md) for build instructions.

## Dependencies

- **Standard C Libraries**: Uses only standard library functions.
- **System Functions**: Uses `system()` to execute other programs.

## File Structure

- `main.c`: Main program entry point.
- `cl.c`: Command interpreter logic.
- `packageManager.c`: Not in use for now.
- `cl.h`: Function declarations and constants.
- `cba.h`, `cxt.h`: Centralized header controllers.
- All remaining `.h` files.

## Notes

- Designed specifically for Windows.
- Uses system calls to execute other executables.
- Integral part of the CLEARNING ecosystem.

## Version

CL v2.0.0 - Author: Nahum Naranjo</content>
<parameter name="filePath">d:\Programacion\CLearning\projects\cl\README.md