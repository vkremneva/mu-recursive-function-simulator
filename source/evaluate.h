#pragma once

#include <ctype.h>
#include "basis.h"
#include "stdlib.h"

int64_t evaluate(struct Function func, struct Arguments arg);

//composition operator
//given an m-ary function h and m k-ary functions g
//arg contains (x1,...,xk)
//returns the evaluation of function h(g1, ..., gm)
int64_t O(struct Function h, struct Operand g, struct Arguments arg);

//primitive recursion operator
//given the (n+2)-ary function h(z, y, x) and n-ary function g(x)
//x = (x1, ..., xn)
//arg contains (y, x)
//returns the evaluation of function f where
//f(0, x) = g(x)
//f(y+1, x) = h(f(y, x), y, x)
int64_t R(struct Function h, struct Function g, struct Arguments arg);

//minimisation operator
//given (k+1)-ary function g
//arg contains (z, x1, ..., xk)
//beginning the search from 0 and proceeding upwards — the smallest
//argument that causes the function to return zero;
//if there is no such argument, the search never terminates.
int64_t M(struct Function g, struct Arguments arg);
