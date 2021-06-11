/**
*
*       Parse variable names
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


static void get_vm_variable(__VARIABLE* v, char* buffer)
{
    char *name;
    name = get_vm_name(v->kind);

    sprintf(buffer, "%s %i", name, v->index);

    return;
}

void get_variable(CODE* c, char* varname, char* buffer)
{
    __VARIABLE* v = search_table(c->table, varname);
    get_vm_variable(v, buffer);
    return;
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

    // Prevent the release_table function from destroying the outer scope
    t->next = NULL;

    release_table(&t);

    return;
}
