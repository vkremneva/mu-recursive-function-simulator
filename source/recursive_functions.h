#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

//z() is a null-function
//returns zero in any case
extern bool Z(int64_t x);

//s() is a successor function
//returns x+1
extern int64_t S(int64_t x);

//identify function P[k, m](x1, x2, x3, ..., xm)
//returns xk
extern int64_t P(int64_t k, int64_t m, int64_t *args);
