file(GLOB SOURCES "*.c") 
file(GLOB HEADERS "*.h")

add_library(cfm_lib STATIC ${SOURCES} ${HEADERS})
target_include_directories(cfm_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(cfm_lib PRIVATE common)