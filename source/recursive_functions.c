//#include <stdarg.h> //accessing the optional arguments of functions that support them (“Variable Numbers of Arguments”)
//#include <stdlib.h> //memory, sorting, integer arithmetic

#include "recursive_functions.h"

extern bool z(int x) {return 0;}

extern int s(int x) {return x+1;}

//extern int i

extern int sum(int x, int y) {
	if (y == 0)
		return x;
	else 
		return s(sum(x, y-1));
}

extern int prod(int x, int y) {
	if (y == 0)
		return 0;
	else
		return sum(x, prod(x, y-1));
}

extern int c(int k, int x) {
	if (k == 0)
		return z(x);
	else
		return s(c(k-1, x));
}

extern bool n(int x) {
	if (x == 0)
		return 1;
	else
		return z(x-1);
}

extern bool p(int x) {
	if (x == 0)
		return 0;
	else
		return n(p(x-1));
}

//TODO: memory, check
/*int fact2(int x, int y) {
	if (x == 0)
		return c(1, y);
	else
		return prod(s(x-1), fact2(x-1, y));
}

extern int fact(int x) {
	return fact2(i(1, 1, x), z(x))
}*/

/*int pred2(int x, int y) {
	if (x == 0)
		return z(y);
	else
		return i(2, 3, pred2(x-1, y), x-1, y);
}

extern int pred(int x) {
	return pred2(x, z(x));
}

как ты работаешь с отрицательными значениями?
extern int subs(int x, int y) {
}
	if (y == 0)
		return x;
	else
		return pred(subs(x, y-1));
}*/

bool ispositive(int x) {
	return n(n(x));
}

/*extern bool neq(int x, int y) {
	return ispositive(sum(subs(x, y), subs(y, x)));
}

extern bool eq(int x, int y) {
	return n(subs(x, y));
}*/