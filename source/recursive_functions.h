#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>

typedef unsigned int uint;

//z() is a null-function
//returns zero in any case
extern bool z(uint x);

//s() is a successor function
//returns x+1
extern uint s(uint x);

//identify function i[k, m](x1, x2, x3, ..., xm)
//returns xk
extern uint i(uint k, uint m, ... );

//returns x + y
extern uint sum(uint x, uint y);

//returns x * y
extern uint prod(uint x, uint y);

//c() is a function to define a constant
//returns k
extern uint c(uint k, uint x);

//n() is null detector
//returns 1 if x is null and 0 otherwise
extern bool n(uint x);

//return 1 if x is even number and 0 otherwise
extern bool p(uint x);

//returns x!
extern uint fact(uint x);

//returns x-1
extern uint pred(uint x);

//returns x-y
extern uint subs(uint x, uint y);

//returns 1 if x is not equal y and 0 otherwise
extern bool neq(uint x, uint y);

//returns 1 if x=y and 0 otherwise
extern bool eq(uint x, uint y);