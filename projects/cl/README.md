# CL - Command-Line Tool Launcher

CL is the primary launcher for the CLEARNING ecosystem. It provides a unified interface to run other tools (HUB, CXT, CBA), includes a small calculator, and can install helper packages.

---

## Features

- **Tool launcher**: Run tools like `hub`, `cxt`, and `cba` from a single entrypoint.
- **Built-in calculator**: Evaluate expressions with operator precedence and trig functions.
- **Version reporting**: Query versions of CL and supported tools.
- **Package installer**: Install helper packages from `common/packages/`.

---

## Usage

### Syntax
```bash
cl [options] [command] [args...]
```

### General Options

- `-h`, `--help` — Show help information.
- `-v`, `--version` — Show version info for CL or one of the supported tools.

### Tool execution

- `exec <tool>` or `-e <tool>` — Execute a supported tool.
  - Supported: `hub`, `cxt`, `cba`

**Examples:**
```bash
cl exec hub
cl exec cxt
cl exec cba
```

### Calculator

- `calc <expression>` or `-c <expression>` — Evaluate a math expression.

**Examples:**
```bash
cl calc "2 + 3 * 4"          # Result: 14
cl -c "s(30) + c(45)"        # Result: 1.207107
```

### Install helper packages

- `install <package>` or `-i <package>`

**Examples:**
```bash
cl install cxt
cl install cui
```

### Running tools with arguments

Some tools accept additional arguments when launched via `cl exec`.

**CXT example (analyze file + show info):**
```bash
cl exec cxt "C:\path\to\file.txt" info -a
```

**CBA example:**
```bash
cl exec cba build
```

---

## Built-in Calculator Details

### Supported operations
- Arithmetic: `+`, `-`, `*`, `/`, `%`
- Trigonometric: `s()` (sine), `c()` (cosine), `t()` (tangent)

### Operator precedence
1. Trigonometric functions
2. Multiplication / Division / Modulo
3. Addition / Subtraction

---

## Build

CL is built as part of the main CLEARNING solution.

```bash
cmake -G Ninja .
ninja
```

The executable is usually located at `build/cl.exe`.

---

## Project Layout

- `main.c`: Entry point.
- `cl.c`: Command interpreter.
- `calc.c`: Calculator implementation.
- `install.c`: Package installer.
- `cl.h`: Header declarations.

---

## Notes

- Designed for Windows (uses `system()` and Windows console helpers).

---

## Version

CL v1.3.3
</content>
<parameter name="filePath">d:\Programacion\CLearning\projects\cl\README.md