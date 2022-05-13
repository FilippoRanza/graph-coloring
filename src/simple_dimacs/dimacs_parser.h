#include <stddef.h>
#include <stdint.h>

typedef enum {
    Comment,
    Problem,
    Node,
    Edge
} EntryType;

typedef enum {
    ParseOk,
    ParseToLong,
    ParseToShort,
    ParseError,
} ParseResult;


typedef struct {
    size_t node_count;
    size_t edge_count;
} ProblemData;

typedef struct {
    size_t node_id;
    int64_t weight;
} NodeData;

typedef struct {
    size_t src;
    size_t dst;
} EdgeData;


typedef struct Parser Parser;

Parser* new_parser();
void free_parser(Parser*);
ParseResult parse_line(Parser*, char*);

ProblemData* get_problem_data(Parser*);
NodeData* get_node_data(Parser*);
EdgeData* get_edge_data(Parser*);
EntryType get_entry_type(Parser*);
