#include "parser.h"

int getc_ns(FILE *stream) {
    int c;
    while (isspace(c = fgetc(stream)));
    return c;
}

void add_function(struct Function *func, struct FuncList *func_list) {
    struct FuncList *new_node = (struct FuncList*)malloc(sizeof(struct FuncList));
    new_node->this = func;
    new_node->next = NULL;

    while (func_list->next != NULL) {
        func_list = func_list->next;
    }
    func_list->next = new_node;
}

struct Function *find_function(char *name, struct FuncList *func_list, struct FuncList **last_node) {
    if (func_list == NULL) {
        *last_node = NULL;
        return NULL;
    }
    do {
        if (strcmp(name, func_list->this->name) == 0) {
            return func_list->this;
        }
        func_list = func_list->next;
    } while (func_list->next != NULL);

    //where is my mind?
    if (func_list->next == NULL) {
        if (strcmp(name, func_list->this->name) == 0) {
            return func_list->this;
        }
    }
    *last_node = func_list;
    return NULL;
}

void parse(FILE *stream, struct FuncList *registered_functions) {
	int c;
    while ((c = getc_ns(stream)) != EOF) {
	    ungetc(c, stream); //back to stream
        parse_declaration(stream, registered_functions);
	}
}

struct Function* parse_declaration(FILE *stream, struct FuncList *registered_functions) {
    char name[NAME_SIZE];
    int i = 0, c;

    while (isalnum(c = getc_ns(stream))) {
        name[i++] = (char)c;
    }
    name[i] = '\0';

    //assert(isalpha(name[0])); //whether we want name to start with a letter
    if (c != '=') {
        fprintf(stderr, "\nError: Unexpected character. Expected '=', was %c\n", c);
        delete_funclist(registered_functions);
        _Exit(9);
    }

    struct Function *new_function = parse_definition(stream, registered_functions);
    c = getc_ns(stream);

    if (c != '.') {
        fprintf(stderr, "\nError: Unexpected character. Expected '.', was %c\n", c);
        delete_funclist(registered_functions);
        _Exit(9);
    }

    strcpy(new_function->name, name);
    return new_function;
}

struct Operand parse_operand(FILE *stream, struct FuncList *registered_functions) {
    struct Operand op;
    op.arity = 0;

    //operator '(' was already read
    //check if the operand is a tuple
    int c = getc_ns(stream);
    if (c == '(') {
        while (c != ')') {
            op.func[op.arity++] = parse_definition(stream, registered_functions);
            c = getc_ns(stream);
            if ((c != ',') && (c != ')')) {
                fprintf(stderr, "\nError: Unexpected character. Expected ',' or ''), was %c\n", c);
                delete_funclist(registered_functions);
                _Exit(9);
            }
        }
    }
    else if (isalnum(c)) {
        ungetc(c, stream);
        op.func[op.arity++] = parse_definition(stream, registered_functions);
    }
    else {
        fprintf(stderr, "\nSyntax error while parsing operand\n");
        delete_funclist(registered_functions);
        _Exit(10);
    }

    return op;
}

struct Function* parse_definition(FILE *stream, struct FuncList *registered_functions) {
    enum PARSER_STATUS status = _parser_status_read_name;

    int c = 0;
    char name[NAME_SIZE] = {0};

    struct Function *new_function = NULL;

    while (status != _parser_status_end) {
        switch (status) {
            case _parser_status_read_name: {
                int i = 0;
                while (isalnum(c = getc_ns(stream))) {
                    name[i++] = (char)c;
                }
                name[i] = '\0';
                if (c == '.' || c == ',' || c == ')') {
                    ungetc(c, stream);
                }
                status = _parser_status_handle_name;
                break;
            }

            case _parser_status_handle_name: {
                if (strcmp(name, "O") == 0) {
                    status = _parser_status_O_operator;
                    break;
                }
                if (strcmp(name, "R") == 0) {
                    status = _parser_status_R_operator;
                    break;
                }
                if (strcmp(name, "M") == 0) {
                    status = _parser_status_M_operator;
                    break;
                }
                if (strcmp(name, "P") == 0) {
                    status = _parser_status_P_function;
                    //Projection function needs its parameters
                    if (c != '[') {
                        fprintf(stderr, "\nError: Unexpected character. Expected '[', was %c\n", c);
                        delete_funclist(registered_functions);
                        _Exit(9);
                    }
                    int k = 0, m = 0;
                    while (isdigit(c = getc_ns(stream))) {
                        k = k * 10 + c - '0';
                    }
                    if (c != ',') {
                        fprintf(stderr, "\nError: Unexpected character. Expected ',', was %c\n", c);
                        delete_funclist(registered_functions);
                        _Exit(9);
                    }
                    while (isdigit(c = getc_ns(stream))) {
                        m = m * 10 + c - '0';
                    }
                    if (c != ']') {
                        fprintf(stderr, "\nError: Unexpected character. Expected ']', was %c\n", c);
                        delete_funclist(registered_functions);
                        _Exit(9);
                    }
                    if (sprintf(name, "P,%d,%d", k, m) <= 0) {
                        fprintf(stderr, "\nError: Fail to write the name of P[]() function\n");
                        delete_funclist(registered_functions);
                        _Exit(11);
                    }
                }

                //check whether new function is already present
                struct FuncList *last_node;
                new_function = find_function(name, registered_functions, &last_node);

                if (status == _parser_status_P_function && new_function == NULL) {
                    new_function = (struct Function*)malloc(sizeof(struct Function));
                    new_function->is_primitive = true;
                    strcpy(new_function->name, name);
                    add_function(new_function, last_node);
                }
                if (new_function == NULL) {
                    fprintf(stderr, "\nError: Unknown name %s\n", name);
                    delete_funclist(registered_functions);
                    _Exit(12);
                }
                status = _parser_status_end;
                break;
            }

            case _parser_status_O_operator: {
                if (c != '(') {
                    fprintf(stderr, "\nError: Unexpected character. Expected '(', was %c\n", c);
                    delete_funclist(registered_functions);
                    _Exit(9);
                }

                // read left operand
                new_function = (struct Function*)malloc(sizeof(struct Function));
                new_function->name[0] = '\0';
                strcpy(new_function->operator, "O");
                new_function->is_primitive = false;
                new_function->left = parse_operand(stream, registered_functions);

                c = getc_ns(stream);
                if (c != ',') {
                    fprintf(stderr, "\nError: Unexpected character. Expected ',', was %c\n", c);
                    delete_funclist(registered_functions);
                    _Exit(9);
                }

                new_function->right = parse_operand(stream, registered_functions);

                c = getc_ns(stream);
                if (c != ')') {
                    fprintf(stderr, "\nError: Unexpected character. Expected ')', was %c\n", c);
                    delete_funclist(registered_functions);
                    _Exit(9);
                }

                add_function(new_function, registered_functions);
                status = _parser_status_end;
                break;
            }

            case _parser_status_R_operator: {
                if (c != '(') {
                    fprintf(stderr, "\nError: Unexpected character. Expected '(', was %c\n", c);
                    delete_funclist(registered_functions);
                    _Exit(9);
                }

                new_function = (struct Function*)malloc(sizeof(struct Function));
                new_function->name[0] = '\0';
                strcpy(new_function->operator, "R");
                new_function->is_primitive = false;
                new_function->left = parse_operand(stream, registered_functions);

                c = getc_ns(stream);
                if (c != ',') {
                    fprintf(stderr, "\nError: Unexpected character. Expected ',', was %c\n", c);
                    delete_funclist(registered_functions);
                    _Exit(9);
                }

                new_function->right = parse_operand(stream, registered_functions);

                c = getc_ns(stream);
                if (c != ')') {
                    fprintf(stderr, "\nError: Unexpected character. Expected ')', was %c\n", c);
                    delete_funclist(registered_functions);
                    _Exit(9);
                }
                add_function(new_function, registered_functions);
                status = _parser_status_end;
                break;
            }

            case _parser_status_M_operator: {
                if (c != '(') {
                    fprintf(stderr, "\nError: Unexpected character. Expected '(', was %c\n", c);
                    delete_funclist(registered_functions);
                    _Exit(9);
                }
                new_function = (struct Function*)malloc(sizeof(struct Function));
                new_function->name[0] = '\0';
                strcpy(new_function->operator, "M");
                new_function->is_primitive = false;
                new_function->left = parse_operand(stream, registered_functions);

                c = getc_ns(stream);
                if (c != ')') {
                    fprintf(stderr, "\nError: Unexpected character. Expected ')', was %c\n", c);
                    delete_funclist(registered_functions);
                    _Exit(9);
                }

                add_function(new_function, registered_functions);
                status = _parser_status_end;
                break;
            }

            default: break;
        }
    }

    return new_function;
}