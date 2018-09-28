#include "basis.h"

bool Z(int64_t x) {return 0;}

int64_t S(int64_t x) {return x+1;}

int64_t P(int64_t k, int64_t m, int64_t *args) {
	if (k > m) {
		fprintf(stderr, "Incorrect argument: in P[k, m] k shoul be less than m\n");
		_Exit(1);
	}

	if (sizeof(args) < m) {
		fprintf(stderr, "Incorrect arguments: in P[k, m](x1, ..., xt) m = t\n"
				  "Here m = %lld, t=%i", m, sizeof(args));
		_Exit(1);
	}

	return args[k-1];
}