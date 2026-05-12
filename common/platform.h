#ifndef PLATFORM_H
#define PLATFORM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#ifdef _WIN32
#include <windows.h>
#include <direct.h>
#define mkdir(path) _mkdir(path)
#define getcwd(buf, size) GetCurrentDirectoryA(size, buf)
#define PATH_SEPARATOR '\\'
#else
#include <unistd.h>
#define mkdir(path) mkdir(path, 0755)
#define PATH_SEPARATOR '/'
#endif

#endif // PLATFORM_H