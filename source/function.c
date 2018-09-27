#include "function.h"

struct Function {
    char name[NAME_SIZE];
    char operator;
    bool left_is_primitive;
    bool right_is_primitive;
    int64_t (*left_primitive)(uint32_t, ... );
    int64_t (*right_primitive)(uint32_t, ... );
    struct Operand (*left)(struct Operand);
    struct Operand (*right)(struct Operand);
};

struct Operand {
    //idk yet
    int8_t arity;
    int64_t (*funcPtr[MAX_ARITY])(uint32_t, ... )
};

int64_t evaluate(struct Function (*func)(char name[NAME_SIZE]), ... ) {
    int64_t result = -1;
    va_list argptr;
    va_start(argptr, func);
    va_arg(argptr, struct Function);

    if (func(argptr).left_is_primitive)
        //а если я хочу передать все аргументы, а не только первый?
        //result = func(argptr).left_primitive(va_copy(va_list dest, argptr));
    else if (func(argptr).right_is_primitive)
        //result = func(argptr).right_primitive(va_copy(va_list dest, argptr));
    else {
        switch (func(argptr).operator) {
            case '0': result = 1;
            case 'P': result = 2;
            case 'R': result = 3;
            case 'M': result = 4;
            default: fprintf(stderr, "Error: Unknown operator %c", func(argptr).operator);
        }
    }

    va_end(argptr);

    if (result < 0) {
        fprintf(stderr, "Error: Something went wrong when evaluating primitive functions");
        _Exit(1);
    }

    return result;
}