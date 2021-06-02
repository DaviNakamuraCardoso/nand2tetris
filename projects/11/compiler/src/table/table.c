/**
*
*           Symbol table for the Davi Compiler Collection
*           (c) 2021 Davi Nakamura Cardoso
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <table/table.h>

TABLE* new_table(char* name, char* type_name, TYPE type, KIND kind, short index)
{
    TABLE* t = NULL;

    t = malloc(sizeof(TABLE));

    t->name =  (name != NULL) ? strdup(name) : NULL;
    t->type_name = (type_name != NULL) ? strdup(type_name) : NULL;
    t->type = type;
    t->kind = kind;
    t->index = index;
    t->next = NULL;

    return t;
}

void release_table(TABLE** table)
{
    free((*table)->name);
    free((*table)->type_name);
    free((*table));

    *table = NULL;

    return;
}
