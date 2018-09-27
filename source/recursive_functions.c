#include "recursive_functions.h"

extern bool Z(uint32_t x, ... ) {return 0;}

extern int64_t S(uint32_t x) {return x+1;}

extern int64_t P(uint32_t k, uint32_t m, ... ) {
	if (k < m) {
		int64_t result = -1;

		va_list argptr;
		va_start(argptr, m);
		for (int64_t i = 0; i < k; i++)
			result = va_arg(argptr, int64_t);

		va_end(argptr);
		
		if (result == -1) {
			fprintf(stderr, "Incorrect argument: no 'x' arguments in P[k, m](x1, ...) function\n");
            _Exit(1);
		}
		return result;
	} else {
		fprintf(stderr, "Incorrect argument: in P[k, m] k shoul be less than m\n");
		_Exit(1);
	}
}