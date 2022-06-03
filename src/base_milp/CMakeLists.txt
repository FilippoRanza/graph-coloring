add_library(
    milp
    milp.c
    milp.h
    free_instance.c
    free_instance.h
    new_instance.c
    new_instance.h
    model.c
    model.h
)

target_include_directories(milp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(milp PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(milp PUBLIC scip)
target_link_libraries(milp PRIVATE simple_dimacs)

enable_testing()

macro(new_milp_test src_file graph_file)
add_executable(
    ${src_file}
    test/${src_file}.c
)
target_link_libraries(${src_file} PUBLIC simple_dimacs)
target_link_libraries(${src_file} PUBLIC milp)
add_test(${src_file} ${src_file} ${PROJECT_SOURCE_DIR}/graphs/${graph_file})

endmacro(new_milp_test)

new_milp_test(test_problem_load graph.txt)
new_milp_test(test_problem_solution graph.txt)






