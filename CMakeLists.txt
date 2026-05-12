cmake_minimum_required(VERSION 3.10)

project(CLEARNING VERSION 1.4.9)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Generate compile_commands.json for IntelliSense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set output directories for Ninja and other generators
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

# Add subdirectories
add_subdirectory(common)
add_subdirectory(projects/cfm)
add_subdirectory(projects/ccmanager)
add_subdirectory(projects/InLine)
add_subdirectory(projects/cl)
add_subdirectory(projects/hub)
add_subdirectory(projects/cba)
add_subdirectory(projects/cui)
add_subdirectory(projects/cxt)