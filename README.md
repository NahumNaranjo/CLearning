# CLEARNING - C Learning Projects Collection

CLEARNING is a set of learning projects written in pure C. It demonstrates a variety of programming concepts such as file handling, command-line interfaces, text analysis, build automation, and more.

---

## Project Components

### Main Tools

- **[CL](projects/cl/README.md)** — Command-line launcher that runs tools, includes a built-in calculator, and can install helper packages.
- **[HUB](projects/hub/README.md)** — Console menu interface for easy tool launching.
- **[CXT](projects/cxt/README.md)** — Text analysis tool for word counts, frequency statistics, and report generation.
- **[CBA](projects/cba/README.md)** — Build assistant that generates CMake files and runs CMake + Ninja.
- **[CFM](projects/cfm/README.md)** — Helper library for file and directory utilities.
- **[CUI](projects/cui/README.md)** — Console UI helper library.

### Shared Library

- **[Common](common/README.md)** — Shared utility library (map data structure, screen management, etc.).

---

## Requirements

- **C Compiler**: GCC (MinGW recommended) or any C11-compatible compiler.
- **CMake**: 3.10 or newer.
- **Ninja**: Used by CBA for builds.
- **Platform**: Windows (project uses Windows console APIs).

---

## Build Instructions

From the repo root:

```bash
cmake -G Ninja .
ninja
```

This generates executables in the `build/` folder:

- `build/cl.exe`
- `build/hub.exe`
- `build/cxt.exe`
- `build/cba.exe`

---

## Usage Examples

### Run the main launcher (CL)
```bash
./build/cl.exe --help
```

### Run HUB (menu interface)
```bash
./build/hub.exe
```

### Run CXT (text analysis)
```bash
./build/cxt.exe
```

For fuller command reference, see [DOCUMENTATION.md](DOCUMENTATION.md).

---

## Contributing

This project is intended as an educational codebase.

- Follow C11 standards.
- Preserve Windows compatibility.
- Keep documentation updated.

---

## License

MIT License — see [LICENSE](LICENSE) for details.

---

CLEARNING v1.4.0 

Author: Nahum Naranjo