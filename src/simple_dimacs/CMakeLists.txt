
add_library (
    simple_dimacs
    simple_dimacs.c
    simple_dimacs.h
    dimacs_parser.c
    dimacs_parser.h
)

target_include_directories(simple_dimacs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_include_directories(simple_dimacs PUBLIC ${PROJECT_SOURCE_DIR}/src/tokenizer)
target_link_libraries(simple_dimacs PUBLIC tokenizer)

enable_testing()

macro(new_test file_name)
    add_executable(
        ${file_name}
        test/${file_name}.c
    )
    target_include_directories(${file_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
    target_link_libraries(${file_name} PUBLIC simple_dimacs)
    add_test(${file_name} ${file_name})
endmacro(new_test)

new_test(test_parse_comment)
new_test(test_parse_edge)
new_test(test_parse_node)
new_test(test_parse_problem)


#add_executable(
#    test-parse-edge
#    test/test_parse_edge.c
#)
#
#
#target_include_directories(test-parse-edge PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
#target_link_libraries(test-parse-edge PUBLIC simple_dimacs)
#add_test(test-parse-edge test-parse-edge)