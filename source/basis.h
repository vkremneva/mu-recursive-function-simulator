#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "function.h"

//z() is a null-function
//returns zero in any case
bool Z(struct Arguments args);

//s() is a successor function
//returns x+1
int64_t S(int64_t x);

//projection function P[k, m](x1, x2, x3, ..., xm)
//returns xk
int64_t P(int64_t k, int64_t m, int64_t *args);

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