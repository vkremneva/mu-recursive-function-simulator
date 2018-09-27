#include "function.h"

struct Function {
    char name[NAME_SIZE];
    char operator;
    bool is_primitive;
    struct Operand *left;
    struct Operand *right;
};

struct Operand {
    struct Functin *func;
};

struct Arguments {
    int8_t arity;
    int64_t args[MAX_ARITY];
};

int64_t evaluate(struct Function func, struct Arguments arg) {
    int64_t result = -1;
    int8_t ind;

    if (func.is_primitive) {
        switch (func.name[0]) {
            case 'Z':
                result = Z(arg.args[0]); break;
            case 'S':
                result = S(arg.args[0]); break;
            case 'R':
                //name of P looks like P,k,m where k and m are integer values
                result = P(arg.args[2] - '0', arg.args[4] - '0', arg.args); break;

                //найти и использовать функции, определенные выше во входном файле
            default:
                fprintf(stderr, "Error: Unknown operator %c", func.name[0]);
                ind = 1;
                while(func.name[ind] != '\0') {
                    fprintf(stderr, "%c", func.name[ind]);
                    ind++;
                }
                fprintf(stderr, "\n");
        }

    } else {
        switch (func.operator) {
            case '0':
                result = 1; break;
            case 'P':
                result = 2; break;
            case 'R':
                result = 3; break;
            case 'M':
                result = 4; break;
            default:
                fprintf(stderr, "Error: Unknown operator %c", func.operator);
        }
    }

    if (result < 0) {
        fprintf(stderr, "Error: Something went wrong when evaluating primitive functions");
        _Exit(1);
    }

    return result;
}