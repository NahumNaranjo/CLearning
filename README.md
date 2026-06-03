# CLEARNING - C Learning Projects Collection

CLEARNING is a set of learning projects written in pure C. It demonstrates a variety of programming concepts such as file handling, command-line interfaces, text analysis, build automation, and more.

---

## Project Components

### Main Tools

- **[CXT](projects/cxt/README.md)** — Text analysis tool for word counts, frequency statistics, and report generation. **Download [here](https://github.com/NahumNaranjo/CXT).**
- **[CBA](projects/cba/README.md)** — Build assistant that generates CMake files and runs CMake + Ninja. **Download [here](https://github.com/NahumNaranjo/CBA).**
- **[CFM](projects/cfm/README.md)** — Helper library for file and directory utilities. **Download [here](https://github.com/NahumNaranjo/CFM).**
- **[CUI](projects/cui/README.md)** — Console UI helper library. **Download [here](https://github.com/NahumNaranjo/CUI).**
- **[InLine]()** — Console game engine.

### Internal libraries (not intended to be publicly used)
- **[HUB](projects/hub/README.md)** — Console menu interface for easy tool launching.
- **[CL](projects/cl/README.md)** — Command-line launcher that runs tools, includes a built-in calculator, and can install helper packages.
- **[CCM](projects/ccmanager/ccmanager.h)** - Configuration manager.

### Header only libraries
- **[CList](common/clist.h)** - CPython list style library. **Download [here](https://github.com/NahumNaranjo/CList).**
- **[CMap](common/map.h)** - C# map style library. **Download [here](https://github.com/NahumNaranjo/CMap).**
- **[Hermes](common/hermes.h)** - console screen manager. **Download [here](https://github.com/NahumNaranjo/Hermes).**
- **[Ariadne](common/ariadne.h)** - string manipulator. **Download [here](https://github.com/NahumNaranjo/Ariadne).**
- **[README](common/README.md)** — Shared utility library (map data structure, screen management, etc.).

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

CLEARNING v1.4.14

Author: Nahum Naranjo