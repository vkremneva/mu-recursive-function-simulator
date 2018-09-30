#include<string.h>
#include <assert.h>

#include "evaluate.h"

void test_Z() {
    struct Function z;
    z.is_primitive = true;
    strcpy(z.name, "Z");
    z.left = 0;
    z.right = 0;
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

    struct Function s;
    s.is_primitive = true;
    strcpy(s.name, "S");

    struct Function z;
    z.is_primitive = true;
    strcpy(z.name, "Z");

    struct Arguments arg;
    arg.arity = 1;
    arg.args[0] = 7;

    struct Operand g[3];
    g[0].arity = 1;
    g[0].func[0] = s;
    g[1].arity = 1;
    g[1].func[1] = z;
    g[2].arity = 1;
    g[2].func[2] = s;

    strcpy(h.name, "P,1,3");
    assert (O(h, *g, arg) == 8);

    strcpy(h.name, "P,2,3");
    assert (O(h, *g, arg) == 0);

    strcpy(h.name, "P,3,3");
    assert (O(h, *g, arg) == 8);
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

int main() {
    test_Z();
    test_S();
    test_P();
    test_O();
    test_R();
    test_M();

    return 0;
}


