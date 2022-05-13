add_library(
    tokenizer
    tokenizer.c
    tokenizer.h
)

target_include_directories(tokenizer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


enable_testing()
add_executable(
    test_tokenize
    test/test_tokenize.c
)
target_link_libraries(test_tokenize tokenizer)
add_test(test-tokenizer test_tokenize)


add_executable(
    test_tokenize_empty   
    test/test_tokenize_empty.c   
)

target_link_libraries(test_tokenize_empty  tokenizer)
add_test(test-tokenizer-empty-string test_tokenize_empty)

add_executable(
    test_to_many_tokens  
    test/test_to_many_tokens.c   
)

target_link_libraries(test_to_many_tokens  tokenizer)
add_test(test-to-many-tokens test_to_many_tokens)


