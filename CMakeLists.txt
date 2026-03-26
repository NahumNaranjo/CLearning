cmake_minimum_required(VERSION 3.10)

# Set compiler BEFORE project() call to ensure it's used
# Use MinGW GCC compiler (works better on Windows without Visual Studio)
set(CMAKE_C_COMPILER  C:/MinGW/bin/gcc.exe CACHE FILEPATH C compiler)
# If you need SDCC specifically, install it and use:
# set(CMAKE_C_COMPILER c:/Program Files/SDCC/bin/sdcc.exe CACHE FILEPATH C compiler)

project(CLEARNING VERSION 1.3.0)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Generate compile_commands.json for IntelliSense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add subdirectories
add_subdirectory(common)
add_subdirectory(projects/cfm)
add_subdirectory(projects/cxt)
add_subdirectory(projects/hub)
add_subdirectory(projects/cl)
add_subdirectory(projects/cba)
add_subdirectory(projects/ccmanager)
add_subdirectory(projects/InLine)