#include <string.h>
#include <assert.h>
#include <unistd.h>

#include "parser.h"
#include "evaluate.h"
#include "funclist.h"

#define SEED 50

void test_Z() {
    struct Function z;
    z.is_primitive = true;
    strcpy(z.name, "Z");

    struct Arguments arg;
    arg.arity = (int8_t)SEED;
    for (int i = 0; i < SEED; i++) {
        arg.args[i] = 0 + rand()%SEED;
    }

    evaluate(z, arg);
    assert(evaluate(z, arg) == 0);
}

void test_S() {
    struct Function s;
    s.is_primitive = true;
    strcpy(s.name, "S");

    int64_t num = 0 + rand()%SEED;

    struct Arguments arg;
    arg.arity = 1;
    arg.args[0] = num;

    assert(evaluate(s, arg) == num + 1);
}

void test_P() {
    struct Function p;
    p.is_primitive = true;
    strcpy(p.name, "P,4,10");

    struct Arguments arg;
    arg.arity = 10;
    arg.args[0] = 0 + rand()%SEED;
    for (int i = 1; i < 10; i++)
        arg.args[i] = arg.args[0] + i;

    assert(evaluate(p, arg) == arg.args[0] + 3);
}

void test_O() {
    struct Function h, s, z;
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


void test_parser(FILE *stream, char *name) {
    struct FuncList *registered_functions = register_basis_functions();
    parse(stream, registered_functions);
    struct Arguments arg = {2, {0, 0}};
    struct FuncList *last_node;
    struct Function *func = find_function(name, registered_functions, &last_node);
    if (func == NULL) {
        printf("No such function");
        _Exit(100);
    }
    int64_t res = evaluate(*func, arg);
    assert(res == 0);
    delete_funclist(registered_functions);

}


int main() {
    srand(SEED);
    test_basis();

    FILE *input = fopen("../input.txt", "r");
    test_parser(input, "sum");
    fclose(input);
    return 0;
}


