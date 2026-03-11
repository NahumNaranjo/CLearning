# CL - Command-Line Tool Launcher

CL is a simple command-line tool written in pure C that acts as a launcher to execute different utilities and projects within the CLEARNING ecosystem.

## Features

- **Tool Launching**: Allows executing tools like HUB and CXT from the command line.
- **Built-in Calculator**: Mathematical expression evaluator with proper operator precedence and trigonometric functions.
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
- `-c, calc [expression]`: Executes the built-in calculator.
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

5. **Use calculator**:
   ```bash
   cl calc "10 * 5 + 3"
   cl -c "s(30) + c(45)"
   ```

## Calculator Feature

CL includes a built-in mathematical calculator with the following capabilities:

### Supported Operations
- Basic arithmetic: `+`, `-`, `*`, `/`, `%`
- Trigonometric: `s()` (sine), `c()` (cosine), `t()` (tangent)

### Operator Precedence
1. Trigonometric functions (highest)
2. Multiplication, Division, Modulo
3. Addition, Subtraction (lowest)

### Examples
```bash
cl calc "2 + 3 * 4"        # Result: 14 (respects precedence)
cl calc "100 / 5 - 3"      # Result: 17
cl calc "s(30) + c(45)"    # Result: 1.207107 (sin 30° + cos 45°)
```

For detailed calculator documentation, see [DOCUMENTATION.md](../../DOCUMENTATION.md).

## Building

CL is built automatically as part of the main CLEARNING project. See the [main README](../../README.md) for build instructions.

## Dependencies

- **Standard C Libraries**: Uses only standard library functions.
- **System Functions**: Uses `system()` to execute other programs.

## File Structure

- `main.c`: Main program entry point.
- `cl.c`: Command interpreter logic.
- `calc.c`: Built-in calculator implementation with proper operator precedence.
- `calc.h`: Calculator function declarations.
- `cl.h`: Function declarations and constants.
- `cba.h`, `cxt.h`: Centralized header controllers.
- All remaining `.h` files.

## Notes

- Designed specifically for Windows.
- Uses system calls to execute other executables.
- Integral part of the CLEARNING ecosystem.

## Version

CL v3.0.0 - Author: Nahum Naranjo

## Features

- **Tool Launching**: Allows executing tools like HUB and CXT from the command line.
- **Built-in Calculator**: Mathematical expression evaluator with proper operator precedence and trigonometric functions.
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
- `-c, calc [expression]`: Executes the built-in calculator.
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
   ```

5. **Use calculator**:
   Calculator Feature

CL includes a built-in mathematical calculator with the following capabilities:

### Supported Operations
- Basic arithmetic: `+`, `-`, `*`, `/`, `%`
- Trigonometric: `s()` (sine), `c()` (cosine), `t()` (tangent)

### Operator Precedence
1. Trigonometric functions (highest)
2. Multiplication, Division, Modulo
3. Addition, Subtraction (lowest)

###calc.c`: Built-in calculator implementation with proper operator precedence.
- `calc.h`: Calculator function declarations
```bash
cl calc "2 + 3 * 4"        # Result: 14 (respects precedence)
cl calc "100 / 5 - 3"      # Result: 17
cl calc "s(30) + c(45)"    # Result: 1.207107 (sin 30° + cos 45°)
```

For detailed calculator documentation, see [DOCUMENTATION.md](../../DOCUMENTATION.md).
   cl calc "10 * 5 + 3"
   cl -c "s(30) + c(45)"
   ```bash
   cl -e cxt
   `3`

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

CL v3.1.0 - Author: Nahum Naranjo</content>
<parameter name="filePath">d:\Programacion\CLearning\projects\cl\README.md