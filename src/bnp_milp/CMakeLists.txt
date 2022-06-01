add_library(
    bnp_milp
    pricer_graph_coloring.c
    pricer_graph_coloring.h
    bnp_master.c
    bnp_master.h
    bnp_coloring_struct.h
    bnp_coloring_struct.c
    master_variable_helper.c
    master_variable_helper.h
    create_basic_patterns.c
    create_basic_patterns.h
)

target_include_directories(bnp_milp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(bnp_milp PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(bnp_milp PUBLIC scip)
target_link_libraries(bnp_milp PRIVATE simple_dimacs)

enable_testing()

macro(new_bnp_milp_test src_file graph_file)
add_executable(
    ${src_file}
    test/${src_file}.c
)
target_link_libraries(${src_file} PUBLIC simple_dimacs)
target_link_libraries(${src_file} PUBLIC bnp_milp)
add_test(${src_file} ${src_file} ${CMAKE_CURRENT_SOURCE_DIR}/test/${graph_file})

endmacro(new_bnp_milp_test)






