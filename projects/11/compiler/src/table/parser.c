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
#include <utils/error.h>

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

void update_table(CODE* c, char* classname, KIND k, TYPE t)
{

    char varname[400];

    if (c == NULL)
    {
        return;
    }
    if (c->table == NULL)
    {
        return;
    }

    get_next_token_content(c, varname);

    add_var(c->table, varname, classname, k, t);

    return;
}

static void init_method_arguments(CODE* c)
{
    add_var(c->table, "this", c->table->classname, ARGUMENT, CLASSNAME);
    return;

}

static void init_scope_specifics(CODE* c, __F_TYPE type)
{
    switch (type)
    {
        case METHOD:
        {
            init_method_arguments(c);
        }
    }

    return;
}



void init_scope(CODE* c, __F_TYPE type)
{
    if (c->table == NULL) return;

    TABLE* table = new_table(c->table->classname);

    table->next = c->table;
    c->table = table;

    init_scope_specifics(c, type);

    return;
}


void exit_scope(CODE* c)
{

    if (c->table == NULL) return;

    TABLE* t = c->table;

    // Prevent the code from exiting the global scope
    if (c->table->next == NULL) error("Trying to exit global scope");


    c->table = t->next;
    t->next = NULL;
    
    release_table(&t);

    return;
}
