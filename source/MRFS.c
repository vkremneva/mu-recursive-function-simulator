#include<string.h>
#include <assert.h>
//#include <ctype.h> //classify and convert single characters

#include "evaluate.h"

int main0(int argc, char *argv[]) {

	bool err = false;
	
	if (argc == 1) {
		fprintf(stderr, "Error: Specify file with the input data\n");
		err = true;
	}
	
	FILE *finput = fopen(argv[1], "r");
	if (finput == NULL) {
		fprintf(stderr, "Error: Cannot open the file: %s\n", argv[1]);
		err = true;
	}

	if (!err) {

	} else
		return 1;
	
	fclose(finput);
	
	return 0;
}

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

}

int main() {
	test_Z();
	test_S();
	test_P();
	return 0;
}

void test_1() {
	struct Function func1;
	func1.is_primitive = false;
	strcpy(func1.name, "func_1");
	strcpy(func1.operator, "O");
	func1.left = 0;
}