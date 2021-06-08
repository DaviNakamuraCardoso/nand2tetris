/**
*
 *      Parse variable names
*       (c) 2021 Davi Nakamura Cardoso
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <compengine/compile.h>
#include <table/parser.h>

static char* get_vm_name(KIND kind)
{
    char* kinds[] = {
         "static",
         "this",
         "argument",
         "local"
    };

    return kinds[kind];
}

char* get_vm_variable(__VARIABLE* v)
{
    char* r, *name;

    name = get_vm_name(v->kind);
    r = calloc(sizeof(char), 100);

    sprintf(r, "%s %i", name, v->index);

    return r;
}

void update_table(CODE* c, KIND k, TYPE t)
{
    char* varname = get_next_token_content(c);

    add_var(c->table, varname, k, t);

    free(varname);

    return;
}
