#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>

typedef unsigned int uint;

//z() is a null-function
//returns zero in any case
extern bool Z(uint x, ... );

//s() is a successor function
//returns x+1
extern uint S(uint x);

//identify function P[k, m](x1, x2, x3, ..., xm)
//returns xk
extern uint P(uint k, uint m, ... );
