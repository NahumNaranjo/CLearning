file(GLOB SOURCES CONFIGURE_DEPENDS "*.c")
file(GLOB HEADERS CONFIGURE_DEPENDS "*.h")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

add_executable(cl ${SOURCES} ${HEADERS})

target_link_libraries(cl PRIVATE 
        common
        cfm_lib
        
    )