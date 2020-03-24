CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

project(c_srv_simple_example)

set(C_SRV_LIB "${CMAKE_CURRENT_SOURCE_DIR}/../src")

add_subdirectory(${C_SRV_LIB})

file(GLOB SOURCES "*.c")

add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} c_srv)
