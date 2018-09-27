#pragma once

#include <stdlib.h>
#include "recursive_functions.h"

#define NAME_SIZE 32
#define MAX_ARITY 127

struct Function;

struct Operand;

int64_t evaluate(struct Function (*func)(char name[NAME_SIZE]), ... );

