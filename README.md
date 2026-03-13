# CLEARNING - C Learning Projects Collection

CLEARNING is a collection of learning projects developed in pure C language. This project demonstrates C programming concepts, including file handling, text analysis, console user interfaces, and basic data structures.

## Project Structure

The project is organized into the following components:

### Main Projects

- **[CL](projects/cl/README.md)**: A command-line tool launcher that allows executing different utilities. Includes a built-in calculator with proper operator precedence.
- **[HUB](projects/hub/README.md)**: A simple menu interface to access available tools.
- **[CXT](projects/cxt/README.md)**: A text analysis tool that counts words, frequencies, and generates reports.
- **[CBA](projects/cba/README.md)**: A build helper.
- **[CFM](projects/cfm/README.md)**: C File Manager for project analysis and file operations.
- **[CUI](projects/cui/README.md)**: Command line UI engine.

### Common Library

- **[Common](common/)**: Static library providing shared utilities like map structures and console screen management.

## System Requirements

- **C Compiler**: GCC (MinGW recommended on Windows) or C11 compatible.
- **CMake**: Version 3.10 or higher for project building.
- **Ninja**: Completely required due to being the only one CBA supports for the moment.
- **Operating System**: Windows compatible (tested on Windows with MinGW).

## Building and Installation
### Easy way
Download the installer and run it, it'll install the program to path. You may have problems with windows defender or smart smart app control due to me not wanting to give my soul to microsoft in exchange of .exe's recognition (pay to sign my .exe's). Sorry D:

### Hard way
1. **Clone or download** the repository to your local machine.

2. **Navigate to the project root directory**:
   ```bash
   cd d:\Programacion\CLearning
   ```

3. **Configure with CMake**:
   ```bash
   cmake -G Ninja .
   ```
   Or if you prefer Makefiles:
   ```bash
   cmake .
   ```

4. **Build the project**:
   ```bash
   ninja
   ```
   Or with make:
   ```bash
   make
   ```

This will generate the executables in the corresponding directories:
- `build/cl.exe`
- `build/hub.exe`
- `build/cxt.exe`
- `build/cba.exe`

## Usage

### Run CL (Main Launcher)
```bash
./build/cl.exe --help
```

### Run HUB (Menu Interface)
```bash
./build/hub.exe
```

### Run CXT directly
```bash
./build/cxt.exe
```

For detailed command reference, see [DOCUMENTATION.md](DOCUMENTATION.md).

## Dependencies

- **Standard C Libraries**: All dependencies are part of the C standard library.
- **Windows-specific Functions**: The project uses some Windows API functions for console operations (like `system("cls")`).

## Contributing

This project is educational and designed to learn C programming concepts. If you want to contribute:

1. Ensure code follows C11 standard.
2. Maintain Windows compatibility.
3. Update corresponding documentation.

## License

This project is open source and distributed under the MIT License. See the LICENSE file for more details.

## Author

Developed by Nahum Naranjo as part of a C learning project.

## Version

CLEARNING v1.3.3p1b

See [CHANGELOG.md](CHANGELOG.md) for detailed feature list and changes.</content>
<parameter name="filePath">d:\Programacion\CLearning\README.md