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

add_executable(
    load-instance-test
    test/test_problem_load.c
)
target_link_libraries(load-instance-test PUBLIC simple_dimacs)
target_link_libraries(load-instance-test PUBLIC milp)

add_test(load-instance-test load-instance-test ${CMAKE_CURRENT_SOURCE_DIR}/test/graph.txt)


