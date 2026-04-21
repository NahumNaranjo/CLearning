file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "*.c")
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "*.h")

add_library(cui_lib STATIC ${SOURCES} ${HEADERS})
target_include_directories(cui_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(cui_lib PRIVATE common)
