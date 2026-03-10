# -----------------------------------------------------------------------------
# Common library — shared code used by multiple projects (e.g. cxt)
# -----------------------------------------------------------------------------
# Add all .c source files that belong to this library:
file(GLOB COMMON_SOURCES "*.c")
file(GLOB COMMON_HEADERS "*.h")

# Build as a static library (libcommon.a on Unix, common.lib on Windows with MSVC)
add_library(common STATIC ${COMMON_SOURCES} ${COMMON_HEADERS})

# Any code that links to "common" will get this include path automatically,
# so they can #include "map.h" etc. from the common folder.
target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(common PRIVATE 
    ${CMAKE_SOURCE_DIR}/projects/cba/cba.c
    ${CMAKE_SOURCE_DIR}/projects/cxt/writeFile.c
    ${CMAKE_SOURCE_DIR}/projects/cxt/txtFunctions.c
    ${CMAKE_SOURCE_DIR}/projects/cxt/readFile.c
    ${CMAKE_SOURCE_DIR}/projects/cxt/ui.c
    ${CMAKE_SOURCE_DIR}/projects/cfm/cfm.c
    ${CMAKE_SOURCE_DIR}/projects/cui/cui.c
)

# Use same C standard as the rest of the project
set_target_properties(common PROPERTIES C_STANDARD 11)