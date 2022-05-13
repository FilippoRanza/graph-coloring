cmake_minimum_required(VERSION 3.00)

project(graph-coloring VERSION 0.1.0) 

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wpedantic")

enable_testing()

add_subdirectory(${PROJECT_SOURCE_DIR}/src/simple_dimacs)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/tokenizer)


add_executable(graph-coloring src/main.c)
target_link_libraries(graph-coloring PRIVATE simple_dimacs)

