file(GLOB SOURCES "*.c") 
file(GLOB HEADERS "*.h")

add_library(inl_lib STATIC ${SOURCES} ${HEADERS})
target_include_directories(inl_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(inl_lib PRIVATE common)