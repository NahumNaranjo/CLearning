# CUI - Console UI Helper

CUI is a small library that provides simple console-based UI primitives (menus, prompts, formatting) for CLEARNING tools.

**Part of the CLEARNING project** — a collection of C learning projects. See the [main README](../../README.md) for more information.

## Features

- **Automatic menu creation**: Create a menu and display it with a few calls.
- **Styled titles**: Customize title output using `displayTitle()`.
- **Lightweight**: Designed for small command-line tools.

## Usage

Install the package into your workspace using CL:

```bash
cl install cui
```

Then include the headers:

```c
#include "cui2.h"
```

## File Structure

- `cui.c`: Implementation of UI helpers.
- `cui.h`: Public API declarations.
- `cui2.c`, `cui2.h`: Extended helpers used by CLEARNING tools.

## Version

CUI v1.0.0