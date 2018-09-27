#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

//z() is a null-function
//returns zero in any case
extern bool Z(uint32_t x, ... );

//s() is a successor function
//returns x+1
extern int64_t S(uint32_t x);

//identify function P[k, m](x1, x2, x3, ..., xm)
//returns xk
extern int64_t P(uint32_t k, uint32_t m, ... );
