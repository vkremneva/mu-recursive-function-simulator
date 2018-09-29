#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#define NAME_SIZE 32
#define MAX_ARITY 127

struct Function {
    char name[NAME_SIZE];
    char operator[NAME_SIZE];
    bool is_primitive;
    struct Operand *left;
    struct Operand *right;
};

struct Operand {
    int8_t arity;
    struct Function func[MAX_ARITY];
};

struct Arguments {
    int8_t arity;
    int64_t args[MAX_ARITY];
};
