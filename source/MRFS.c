#include "evaluate.h"
#include "parser.h"
#include "funclist.h"

struct Arguments read_arguments(char current, bool *error);
void skip();

int main(int argc, char *argv[]) {
	if (argc == 1) {
		fprintf(stderr, "\nError: Specify file with the input data\n");
		return 7;
	}
	
	FILE *finput = fopen(argv[1], "r");
	if (finput == NULL) {
		fprintf(stderr, "\nError: Cannot open file: %s\n", argv[1]);
		return 8;
	}

    struct FuncList *registered_functions = register_basis_functions();
    parse(finput, registered_functions);
    printf("Load complete. \n");
    fclose(finput);
    int ind = 0;
    do {
        printf("\nPress 1 if you want to evaluate something and 2 if you want to quit: \n");
        ind = getchar() - '0';

        if ((ind != 1) && (ind != 2))
            fprintf(stderr, "\nError: Wrong key. Try again.\n");

        if (ind == 1) {
            printf("Enter expression: \n");

            struct Function func;
            char name[NAME_SIZE];
            int i = 0, c;
            int64_t result = 0;
            bool is_P = false;

            while (isalnum(c = getc_ns(stdin))) {
                name[i++] = (char)c;
            }
            name[i] = '\0';

            if (c == '[') {
                is_P = true;
                int k = 0, m = 0;
                while (isdigit(c = getc_ns(stdin))) {
                    k = k * 10 + c - '0';
                }
                if (c != ',') {
                    fprintf(stderr, "\nError: Unexpected character. Expected ',', was %c\n", c);
                    skip();
                    continue;
                }
                while (isdigit(c = getc_ns(stdin))) {
                    m = m * 10 + c - '0';
                }
                if (c != ']') {
                    fprintf(stderr, "\nError: Unexpected character. Expected ']', was %c\n", c);
                    skip();
                    continue;
                }
                if (sprintf(name, "P,%d,%d", k, m) <= 0) {
                    fprintf(stderr, "\nError: Fail to write the name of P[]() function\n");
                    skip();
                    continue;
                }
                func.is_primitive = true;
                strcpy(func.name, name);
            }

            struct FuncList *last_node;
            struct Function *pfunc = find_function(name, registered_functions, &last_node);
            if (pfunc == NULL) {
                if (!is_P) {
                    fprintf(stderr, "\nError: There is no such function. Try again.\n");
                    skip();
                    continue;
                }
            } else
                func = *(pfunc);

            bool err = false;
            struct Arguments arg = read_arguments((char)c, &err);
            if (err) {
                fprintf(stderr, "\nError: Incorrect arguments.\n");
                skip();
                continue;
            } else {
                result = evaluate(func, arg);
                printf("Result: %d.\n", result);
            }
            skip();
        }
    } while (ind != 2);

    delete_funclist(registered_functions);

	return 0;
}

struct Arguments read_arguments(char current, bool *error) {
    struct Arguments arg;
    arg.arity = 0;
    for (int i = 0; i < MAX_ARITY; i++)
        arg.args[i] = 0;


    int ch = current;
    if (ch == ']') ch = getchar();
    do {
        if (isdigit(ch))
            arg.args[arg.arity - 1] = arg.args[arg.arity - 1] * 10 + ch - '0';
        else {
            switch(ch) {
                case '(':
                case ',':
                    arg.arity++; break;
                case ' ':
                    break;
                case ')':
                    return arg;
                default:
                    *error = true;
                    return arg;
            }
        }
        ch = getchar();
    } while (ch != ')');
    return arg;
}

void skip() {
    int ch;
    do {
        ch = getchar();
    } while (ch != '\n');
}