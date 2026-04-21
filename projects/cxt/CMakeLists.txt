file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "*.c")
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "*.h")

add_executable(cxt_app ${SOURCES})
target_link_libraries(cxt_app PRIVATE common)