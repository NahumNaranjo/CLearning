file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "*.c")
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "*.h")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

add_executable(cl ${SOURCES} ${HEADERS})

target_sources(cl PRIVATE 
    ${CMAKE_SOURCE_DIR}/projects/cba/cba.c
    ${CMAKE_SOURCE_DIR}/projects/cxt/writeFile.c
    ${CMAKE_SOURCE_DIR}/projects/cxt/txtFunctions.c
    ${CMAKE_SOURCE_DIR}/projects/cxt/readFile.c
    ${CMAKE_SOURCE_DIR}/projects/cxt/ui.c
    ${CMAKE_SOURCE_DIR}/projects/cfm/cfm.c
    ${CMAKE_SOURCE_DIR}/projects/cl/calc.c
)
target_link_libraries(cl PRIVATE common)