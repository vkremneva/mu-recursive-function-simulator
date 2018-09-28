#pragma once

#include <stdlib.h>
#include "basis.h"

#define NAME_SIZE 32
#define MAX_ARITY 127

struct Function;

struct Operand;

struct Arguments;

int64_t evaluate(struct Function func, struct Arguments arg);
