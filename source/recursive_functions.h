#include <stdbool.h>

//z() is a null-function
//returns zero in any case
extern bool z(int x);

//s() is a successor function
//returns x+1
extern int s(int x);

//extern int i(int k, int m, далее неопределенное количество переменных)

//sum() is a summation function
//returns the sum of x and y
extern int sum(int x, int y);

//prod() is a multiplication function
//returns x * y
extern int prod(int x, int y);

//c() is a function to define a constant
//returns k
extern int c(int k, int x);

//n() is null detector
//returns 1 if x is null and 0 otherwise
extern bool n(int x);

//p() is a parity check function
//return 1 if x is even number and 0 otherwise
extern bool p(int x);

//returns x!
//extern int fact(int x);

//what are you? prbbly to alphabet
//extern int pred(int x);

//returns x-y
//extern int subs(int x, int y);

//returns 1 if x is not equal y and 0 otherwise
extern bool neq(int x, int y);

//returns 1 if x=y and 0 otherwise
extern bool eq(int x, int y);

//mu func?