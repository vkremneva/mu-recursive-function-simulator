#include "basis.h"

int64_t Z(struct Arguments arg) {
    if (arg.args[0] == 0)
        return (bool)arg.args[0];
    else
        return !((bool)arg.args[0]);
}

int64_t S(int64_t x) {return x+1;}

int64_t P(int64_t k, int64_t m, int64_t *arg) {
	if (k > m) {
		fprintf(stderr, "Incorrect argument: in P[k, m] k should be less than m\n");
		_Exit(1);
	}

	return arg[k-1];
}