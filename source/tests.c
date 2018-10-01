#include<string.h>
#include <assert.h>
#include <unistd.h>

#include "parser.h"
#include "evaluate.h"

struct Function s, z;

void test_Z() {
    struct Function z;
    z.is_primitive = true;
    strcpy(z.name, "Z");
    struct Arguments arg;
    arg.arity = 2;
    arg.args[0] = 4, arg.args[1] = 2;
    evaluate(z, arg);

    assert(evaluate(z, arg) == 0);

    arg.arity = 0;
    assert(evaluate(z, arg) == 0);
}

void test_S() {
    struct Function s;
    s.is_primitive = true;
    strcpy(s.name, "S");

    struct Arguments arg;
    arg.arity = 0;

    for (int i = 0; i < 10; ++i) {
        arg.args[0] = i;
        assert(evaluate(s, arg) == i + 1);
    }
}

void test_P() {
    struct Function p;
    p.is_primitive = true;
    strcpy(p.name, "P,4,10");

    struct Arguments arg;
    arg.arity = 10;

    for (int i = 0; i < 10; i++)
        arg.args[i] = i+1;

    assert(evaluate(p, arg) == 4);
}

void test_O() {
    struct Function h;
    h.is_primitive = true;

    s.is_primitive = true;
    strcpy(s.name, "S");

    z.is_primitive = true;
    strcpy(z.name, "Z");

    struct Arguments arg;
    arg.arity = 1;
    arg.args[0] = 7;

    struct Operand g;
    g.arity = 3;
    g.func[0] = &s;
    g.func[1] = &z;
    g.func[2] = &s;

    strcpy(h.name, "P,1,3");
    assert (O(h, g, arg) == 8);

    strcpy(h.name, "P,2,3");
    assert (O(h, g, arg) == 0);

    strcpy(h.name, "P,3,3");
    assert (O(h, g, arg) == 8);
}

void test_R() {
    struct Function h;
    h.is_primitive = true;
    strcpy(h.name, "P,1,3");

    struct Function g;
    g.is_primitive = true;
    strcpy(g.name, "S");

    struct Arguments arg;
    arg.arity = 2;
    arg.args[0] = 1;
    arg.args[1] = 3;

    assert (R(h, g, arg) == 4);
}

void test_M() {
    struct Function g;
    g.is_primitive = true;
    strcpy(g.name, "P,1,3");

    struct Arguments arg;
    arg.arity = 3;
    arg.args[0] = -3;
    arg.args[1] = 100;
    arg.args[2] = 200;

    assert(M(g, arg) == 0);
}

void test_basis() {
    test_Z();
    test_S();
    test_P();
    test_O();
    test_R();
    test_M();
}



struct FuncList *register_basis_functions() {
    struct FuncList *registered_functions = (struct FuncList*)malloc(sizeof(struct FuncList));
    struct FuncList *node = registered_functions;
    struct Function *func = (struct Function*)malloc(sizeof(struct Function));

    strcpy(func->name, "S");
    func->is_primitive = true;
    node->this = func;

    node->next = (struct FuncList*)malloc(sizeof(struct FuncList));
    node = node->next;

    func = (struct Function*)malloc(sizeof(struct Function));
    strcpy(func->name, "Z");
    func->is_primitive = true;
    node->this = func;
    node->next = NULL;

    return registered_functions;
}

void delete_funclist(struct FuncList* list) {
    struct FuncList *next;
    while (list != NULL) {
        next = list->next;
        free(list->this);
        free(list);
        list = next;
    }
}

void test_parser(FILE *stream) {
    struct FuncList *registered_functions = register_basis_functions();
    parse(stream, registered_functions);
    struct Arguments arg = {2, {0, 0}};
    assert(evaluate(*find_function("sum", registered_functions, 0), arg) == 0);
    delete_funclist(registered_functions);
}



int main() {
    //test_basis();

    FILE *input = fopen("../input.txt", "r");
    test_parser(input);
    fclose(input);
    return 0;
}


