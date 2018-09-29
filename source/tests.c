#include<string.h>
#include <assert.h>

#include "evaluate.h"

void test_Z() {
    struct Function s;
    s.is_primitive = true;
    strcpy(s.name, "Z");
    s.left = 0;
    s.right = 0;
    struct Arguments arg;
    arg.arity = 2;
    arg.args[0] = 4, arg.args[1] = 2;
    evaluate(s, arg);

    assert(evaluate(s, arg) == 0);

    arg.arity = 0;
    assert(evaluate(s, arg) == 0);
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

int main() {
    test_Z();
    test_S();
    test_P();
    return 0;
}


