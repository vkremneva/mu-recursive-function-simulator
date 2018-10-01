#include "funclist.h"

struct FuncList *register_basis_functions() {
    struct FuncList *registered_functions = (struct FuncList*)malloc(sizeof(struct FuncList));
    struct FuncList *node = registered_functions;
    struct Function *func = (struct Function*)malloc(sizeof(struct Function));

    strcpy(func->name, "S");
    func->is_primitive = true;
    node->this = func;

    node->next = (struct FuncList*)malloc(sizeof(struct FuncList));
    node = node->next;

    func = (struct Function*)malloc(sizeof(struct Function));
    strcpy(func->name, "Z");
    func->is_primitive = true;
    node->this = func;
    node->next = NULL;

    return registered_functions;
}

void delete_funclist(struct FuncList* list) {
    struct FuncList *next;
    while (list != NULL) {
        next = list->next;
        free(list->this);
        free(list);
        list = next;
    }
}
