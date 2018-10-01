#include "evaluate.h"

int64_t evaluate(struct Function func, struct Arguments arg) {
    int64_t result = -1;
    int8_t ind;

    if (func.is_primitive) {
        switch (func.name[0]) {
            case 'Z':
                result = Z(arg);
                break;
            case 'S':
                result = S(arg.args[0]);
                break;
            case 'P': {
                //name of P looks like P,k,m where k and m are integer values
                char ch;
                int64_t i = 2, k = 0, m = 0;

                while (isdigit(ch = func.name[i++]))
                    k = k*10 + (ch - '0');

                while (isdigit(ch = func.name[i++]))
                    m = m*10 + (ch - '0');

                result = P(k, m, arg.args);
                break;
            }
            default:
                fprintf(stderr, "Error: Unknown primitive function %c \n", func.name[0]);
        }

    } else {
        switch (func.operator[0]) {
            case 'O':
                result = O(*(func.left.func[0]), func.right, arg);
                break;
            case 'R':
                result = R(*(func.left.func[0]), *(func.right.func[0]), arg);
                break;
            case 'M':
                result = M(func, arg);
                break;
            default:
                fprintf(stderr, "Error: Unknown operator %s \n", func.operator);
                _Exit(1);
        }
    }

    if (result < 0) {
        fprintf(stderr, "Error: Something went wrong when evaluating function %c", func.name[0]);
        ind = 1;
        while (func.name[ind] != '\0') {
            fprintf(stderr, "%c", func.name[ind]);
            ind++;
        }
        fprintf(stderr, "\n");
        _Exit(1);
    }

    return result;
}

int64_t O(struct Function h, struct Operand g, struct Arguments arg){
    struct Arguments args_for_h;
    args_for_h.arity = g.arity;

    for (int i = 0; i < g.arity; i++)
        args_for_h.args[i] = evaluate(*g.func[i], arg);

    return evaluate(h, args_for_h);
}

int64_t R(struct Function h, struct Function g, struct Arguments arg){
    if (arg.arity <= 1) {
        fprintf(stderr, "Error: Arity can't be 1 or less. Was %d.\n", arg.arity);
        _Exit(1);
    }

    int64_t arg0;
    struct Arguments step_arg, final_arg;

    if (arg.args[0] == 0) {
        step_arg.arity = arg.arity - (int8_t)1;
        for (int i = 0; i < step_arg.arity; i++)
            step_arg.args[i] = arg.args[i + 1];

        return evaluate(g, step_arg);
    } else {
        step_arg.arity = arg.arity;
        for (int i = 0; i < step_arg.arity; i++)
            step_arg.args[i] = arg.args[i];
        step_arg.args[0] -= 1;

        arg0 = R(h, g, step_arg);

        final_arg.arity = arg.arity + (int8_t)1;
        final_arg.args[0] = arg0;
        for (int i = 0; i < arg.arity; i++)
            final_arg.args[i+1] = arg.args[i];

        return evaluate(h, final_arg);
    }
}

int64_t M(struct Function g, struct Arguments arg) {
    struct Arguments new_arg;

    new_arg.arity = arg.arity;
    for (int i = 1; i < new_arg.arity; i++)
        new_arg.args[i] = arg.args[i];
    new_arg.args[0] = -1;

    do {
        if (new_arg.args[0] == INT64_MAX) {
            fprintf(stderr, "Error: Function in M operator does not converge");
            _Exit(1);
        }

        new_arg.args[0]++;

    } while (evaluate(g, new_arg) != 0);

    return new_arg.args[0];
}
