#include "function.h"

int64_t evaluate(struct Function func, struct Arguments arg) {
    int64_t result = -1;
    int8_t ind;

    if (func.is_primitive) {
        switch (func.name[0]) {
            case 'Z':
                result = Z(arg.args[0]); break;
            case 'S':
                result = S(arg.args[0]); break;
            case 'P':
                //name of P looks like P,k,m where k and m are integer values
                result = P(arg.args[2] - '0', arg.args[4] - '0', arg.args); break;
            default:
                fprintf(stderr, "Error: Unknown primitive function %c \n", func.name[0]);
        }

    } else {
        switch (func.operator) {
            case '0':
                result = 1; break;
            case 'R':
                result = 3; break;
            case 'M':
                result = 4; break;
            default:
                fprintf(stderr, "Error: Unknown operator %c \n", func.operator);
        }
    }

    if (result < 0) {
        fprintf(stderr, "Error: Something went wrong when evaluating function %c", func.name[0]);
        ind = 1;
        while(func.name[ind] != '\0') {
            fprintf(stderr, "%c", func.name[ind]);
            ind++;
        }
        fprintf(stderr, "\n");
        _Exit(1);
    }

    return result;
}