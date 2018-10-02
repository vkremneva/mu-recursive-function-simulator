#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "function.h"

//z() is a null-function
//returns zero in any case
int64_t Z(struct Arguments args);

//s() is a successor function
//returns x+1
int64_t S(int64_t x);

//projection function P[k, m](x1, x2, x3, ..., xm)
//returns xk
int64_t P(int64_t k, int64_t m, int64_t *args);