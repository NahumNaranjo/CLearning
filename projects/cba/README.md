# CBA - Build Assistant for C Projects

CBA is a lightweight build assistant written in C. It can auto-generate a `CMakeLists.txt` and run CMake+Ninja to build your project.

**Part of the CLEARNING project** — a collection of C learning projects. See the [main README](../../README.md) for more information.

## Features

- Auto-detects a C project and generates a `cba.build` file.
- Generates `CMakeLists.txt` that includes all `.c` and `.h` sources.
- Runs CMake + Ninja to configure the build.
- Provides `build`, `init`, and `clean` commands.

## Usage

Run the executable and supply one of the supported commands:

```bash
./cba.exe init   # Generate/refresh cba.build
./cba.exe build  # Generate CMake files and configure build
./cba.exe clean  # Remove the build/ directory
```

You can also run these via CL:

```bash
cl exec cba init
cl exec cba build
cl exec cba clean
```

## Building

CBA is built as part of the main CLEARNING project.

```bash
cmake -G Ninja .
ninja
```

## Dependencies

- **CMake 3.10+**
- **Ninja**

## File Structure

- `main.c`: CLI argument parsing.
- `cba.c`: Core build logic (auto-detection, file generation, CMake runner).
- `ui.c`: User messaging and prompts.

## Notes

- If `cba.build` is missing, `cba build` will automatically generate it.
- `cba init` regenerates `cba.build` based on the current directory.

## Version

CBA v1.0.0