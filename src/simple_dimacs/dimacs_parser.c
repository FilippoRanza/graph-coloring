#include "dimacs_parser.h"
#include <tokenizer.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOKENS 20
#define QUICK_FAIL(function) {ParseResult __result__ = function; if(__result__ != ParseOk) {return __result__;}}




struct Parser {
    Tokens* tokens;
    EntryType type;
    void* ptr;
};

#define CAST_POINTER(type, name) type* name(Parser* parser) { return (type*) parser->ptr; }

CAST_POINTER(ProblemData, get_problem_data)
CAST_POINTER(NodeData, get_node_data)
CAST_POINTER(EdgeData, get_edge_data)

size_t get_generic_buffer_size() {
    size_t problem_data_size = sizeof(ProblemData);
    size_t node_data_size = sizeof(NodeData);
    size_t edge_data_size = sizeof(EdgeData);
    if(problem_data_size > node_data_size) 
        return problem_data_size > edge_data_size ? problem_data_size: edge_data_size;
    else
        return node_data_size > edge_data_size ? node_data_size: edge_data_size;
}

Parser* new_parser() {
    Tokens* tokens = new_tokens(MAX_TOKENS);
    if(tokens == NULL) 
        return NULL;

    Parser* parser = malloc(sizeof(Parser));
    if(parser == NULL) {
        free_tokens(tokens);
    }

    void* ptr = malloc(get_generic_buffer_size());
    if(ptr == NULL) {
        free_tokens(tokens);
        free(parser);
    }

    parser->ptr = ptr;
    parser->tokens = tokens;

    return parser;
}



void free_parser(Parser* parser) {
    free_tokens(parser->tokens);
    free(parser->ptr);
    free(parser);
}



ParseResult get_type(char* token, EntryType* output) {
    int len = strlen(token);
    if(len != 1)
        return ParseError;

    switch(*token) {
        case 'c':
            *output = Comment;
            break;
        case 'p':
            *output = Problem;
            break;
        case 'n':
            *output = Node;
            break;
        case 'e':
            *output = Edge;
            break;
        default:
            return ParseError;
    }
    return ParseOk;    
}

ParseResult check_token_count(Parser* parser, size_t min, size_t max) {
    int len = tokens_count(parser->tokens);
    if(len < min)
        return ParseToShort;
    if(len > max) 
        return ParseToLong;
    return ParseOk;
}


ParseResult parse_problem_def(Parser* parser) {
    QUICK_FAIL(check_token_count(parser, 4, 4))

    char** tokens = tokens_buff(parser->tokens);
    ProblemData* data = get_problem_data(parser);
    data->node_count = atoi(tokens[2]);
    data->edge_count = atoi(tokens[3]);

    return ParseOk;
}
ParseResult parse_node_def(Parser* parser) {
    QUICK_FAIL(check_token_count(parser, 3, 3))
    char** tokens = tokens_buff(parser->tokens);
    NodeData* data = get_node_data(parser);
    data->node_id = atoi(tokens[1]);
    data->weight = atoi(tokens[2]);

    return ParseOk;

}
ParseResult parse_edge_def(Parser* parser) {
    QUICK_FAIL(check_token_count(parser, 3, 3))
    char** tokens = tokens_buff(parser->tokens);
    EdgeData* data = get_edge_data(parser);
    data->src = atoi(tokens[1]);
    data->dst = atoi(tokens[2]);

    return ParseOk;

}

ParseResult parse_line(Parser* parser, char* line) {

    TokenizerResult result = tokenize(parser->tokens, line);
    if(result == BuffOut)
        return ParseToLong;
    QUICK_FAIL( check_token_count(parser, 1, MAX_TOKENS) );

    char** tokens = tokens_buff(parser->tokens);

    EntryType type;
    QUICK_FAIL ( get_type(*tokens, &type) );

    parser->type = type;

    switch (type) {
        case Comment:
            break;
        case Problem:
            QUICK_FAIL( parse_problem_def(parser) )
            break;
        case Node:
            QUICK_FAIL( parse_node_def(parser) )
            break;
        case Edge:
            QUICK_FAIL( parse_edge_def(parser) )
            break;
    }


    return ParseOk;
}


EntryType get_entry_type(Parser* parser) {
    return parser->type;
}