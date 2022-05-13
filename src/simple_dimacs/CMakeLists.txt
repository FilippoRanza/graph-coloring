
add_library (
    simple_dimacs
    simple_dimacs.c
    simple_dimacs.h
)

target_include_directories(simple_dimacs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

enable_testing()
