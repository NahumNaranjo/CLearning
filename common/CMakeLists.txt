# -----------------------------------------------------------------------------
# Common library — shared code used by multiple projects (e.g. cxt)
# -----------------------------------------------------------------------------
# Add all .c source files that belong to this library:
file(GLOB COMMON_SOURCES "*.c")

# Build as a static library (libcommon.a on Unix, common.lib on Windows with MSVC)
add_library(common STATIC ${COMMON_SOURCES})

# Any code that links to "common" will get this include path automatically,
# so they can #include "map.h" etc. from the common folder.
target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Use same C standard as the rest of the project
set_target_properties(common PROPERTIES C_STANDARD 11)