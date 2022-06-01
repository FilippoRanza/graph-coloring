cmake_minimum_required(VERSION 3.00)

project(graph-coloring VERSION 0.1.0) 
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS_DEBUG_INIT "-Wall -Wpedantic -g -O0")
set(CMAKE_C_FLAGS_RELEASE_INIT "-Wall -Wpedantic -g0 -O2")

enable_testing()

add_subdirectory(${PROJECT_SOURCE_DIR}/src/tokenizer)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/simple_dimacs)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/base_milp)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/bnp_milp)


add_executable(graph-coloring src/main.c)
target_link_libraries(graph-coloring PRIVATE simple_dimacs)
target_link_libraries(graph-coloring PRIVATE milp)

add_executable(bnp-graph-coloring src/bnp_main.c)
target_link_libraries(bnp-graph-coloring PRIVATE simple_dimacs)
target_link_libraries(bnp-graph-coloring PRIVATE bnp_milp)

