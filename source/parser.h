#pragma once

#include <assert.h>
#include "stdio.h"
#include "ctype.h"
#include "function.h"
#include "string.h"
#include "funclist.h"

enum PARSER_STATUS {
    _parser_status_read_name,
    _parser_status_handle_name,
    _parser_status_O_operator,
    _parser_status_R_operator,
    _parser_status_M_operator,
    _parser_status_P_function,
    _parser_status_end
};

//Register new function in FuncList
void add_function(struct Function *func, struct FuncList *func_list);

// last_node is meaningful only if search returns NULL
struct Function *find_function(char *name, struct FuncList *func_list, struct FuncList **last_node);

//Get non-space character
int getc_ns(FILE *stream);

//Main parser function
int parse(FILE *stream, struct FuncList *registered_functions);

struct Function* parse_declaration(FILE *stream, struct FuncList *registered_functions);

//Parse ONE operand, invoke parse_definition as may times as needed
struct Operand parse_operand(FILE *stream, struct FuncList *registered_functions);

//Parse ONE function, invoke parse_operand if needed
struct Function* parse_definition(FILE *stream, struct FuncList *registered_functions);