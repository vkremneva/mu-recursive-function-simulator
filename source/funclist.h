#pragma once

#include <malloc.h>
#include <stdbool.h>
#include <string.h>

#include "function.h"

struct FuncList {
    struct Function* this;
    struct FuncList* next;
};

struct FuncList *register_basis_functions();

void delete_funclist(struct FuncList* list);
