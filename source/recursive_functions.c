//#include <stdlib.h> //memory, sorting, uinteger arithmetic

#include "recursive_functions.h"

//TODO: result is too big
extern bool Z(uint x, ... ) {return 0;}

extern uint S(uint x) {return x+1;}

extern uint P(uint k, uint m, ... ) {
	if (k < m) {
		int result = -1;

		va_list argptr;
		va_start(argptr, m);
		for (uint i = 0; i < k; i++)
			result = va_arg(argptr, uint)

		va_end(argptr);
		
		if (result == -1) {
			fpruintf(stderr, "Incorrect argument: no 'x' arguments in P[k, m](x1, ...) function\n");
			exit(1);
		}
		return (uint)result;
	} else {
		fpruintf(stderr, "Incorrect argument: in P[k, m] k shoul be less than m\n");
		exit(1);
	}
}