# CFM - Automatic File Manager

CFM is a small helper library that provides basic file- and directory-related utilities used by the CLEARNING ecosystem.

**Part of the CLEARNING project** — a collection of C learning projects. See the [main README](../../README.md) for more information.

## Features

- **Path resolution**: Find files by name and build paths relative to a root folder.
- **Directory listing**: List files or directories that match a pattern.
- **Root helpers**: Utilities for working with a configured root directory.

## Usage

CFM is intended as a library dependency. It can be installed into a workspace using `cl install`.

```bash
cl install cfm
```

Then include the headers in your project:

```c
#include "cfm2.h"
```

## File Structure

- `cfm.c`: Core implementation.
- `cfm.h`: Public API declarations.
- `cfm2.c` / `cfm2.h`: Additional helper functions.

## Version

CFM v1.1.1