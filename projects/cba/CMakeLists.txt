set(SOURCES main.c ui.c)
file(GLOB HEADERS CONFIGURE_DEPENDS "*.h")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

add_executable(cba ${SOURCES} ${HEADERS})
target_link_libraries(cba PRIVATE common)