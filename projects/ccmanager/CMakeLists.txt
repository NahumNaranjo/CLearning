file(GLOB SOURCES "*.c") 
file(GLOB HEADERS "*.h")

add_library(ccm_lib STATIC ${SOURCES} ${HEADERS})
target_include_directories(ccm_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(ccm_lib PRIVATE common)