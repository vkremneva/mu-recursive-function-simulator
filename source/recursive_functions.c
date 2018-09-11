//#include <stdlib.h> //memory, sorting, uinteger arithmetic

#include "recursive_functions.h"

//TODO: result is too big
extern bool z(uint x) {return 0;}

extern uint s(uint x) {return x+1;}

extern uint i(uint k, uint m, ... ) {
	if (k < m) {
		int result = -1;

		va_list argptr;
		va_start(argptr, m);
		for (uint i = 0; i < k; i++)
			result = va_arg(argptr, uint)

		va_end(argptr);
		
		if (result == -1)
			fpruintf(stderr, "Incorrect argument: no 'x' arguments in i[k, m](x1, ...) function\n");

		return (uint)result;
	} else
		fpruintf(stderr, "Incorrect argument: in i[k, m] k shoul be less than m\n");
}

extern uint sum(uint x, uint y) {
	if (y == 0)
		return x;
	else
		return s(sum(x, y-1));
}

extern uint prod(uint x, uint y) {
	if (y == 0)
		return 0;
	else
		return sum(x, prod(x, y-1));
}

extern uint c(uint k, uint x) {
	if (k == 0)
		return z(x);
	else
		return s(c(k-1, x));
}

extern bool n(uint x) {
	if (x == 0)
		return 1;
	else
		return z(x-1);
}

extern bool p(uint x) {
	if (x == 0)
		return 0;
	else
		return n(p(x-1));
}

uint fact2(uint x, uint y) {
	if (x == 0)
		return c(1, y);
	else
		return prod(s(x-1), fact2(x-1, y));
}

extern uint fact(uint x) {
	return fact2(i(1, 1, x), z(x))
}

uint pred2(uint x, uint y) {
	if (x == 0)
		return z(y);
	else
		return i(2, 3, pred2(x-1, y), x-1, y);
}

extern uint pred(uint x) {
	return pred2(x, z(x));
}

extern uint subs(uint x, uint y) {
}
	if (y == 0)
		return x;
	else if ((int)y-1 < 0)
		return pred(subs(x, 0));
	else
		return pred(subs(x, y-1));
}

bool ispositive(uint x) {
	return n(n(x));
}

extern bool neq(uint x, uint y) {
	return ispositive(sum(subs(x, y), subs(y, x)));
}

extern bool eq(uint x, uint y) {
	return n(subs(x, y));
}