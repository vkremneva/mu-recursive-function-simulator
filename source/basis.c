#include "basis.h"

bool Z(struct Arguments args) {return 0;}

int64_t S(int64_t x) {return x+1;}

int64_t P(int64_t k, int64_t m, int64_t *arg) {
	if (k > m) {
		fprintf(stderr, "Incorrect argument: in P[k, m] k shoul be less than m\n");
		_Exit(1);
	}

	return arg[k-1];
}