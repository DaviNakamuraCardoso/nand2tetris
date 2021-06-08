/**
*
*       Test the parser module for tables
*       (c) 2021 Davi Nakamura Cardoso
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <compengine/compile.h>
#include <compengine/structure.h>
#include <table/parser.h>
#include <utils/tests.h>
#include <utils/tabletests.h>

static unsigned int test_vm_code(void)
{
    TABLE* t = new_table("Main");
    __VARIABLE* v = new_variable("l", STATIC, INT);
    char* cmd = get_vm_variable(v);
    int status = 1;

    add_hash(t, v);

    if (strcmp(cmd, "static 0") != 0)
    {
        status = 0;
    }
    release_table(&t);
    free(cmd);

    return status;

}

static unsigned int test_symbol_table(void)
{
    __VARIABLE* variable1[] = {
            new_variable("high", FIELD, INT),
            new_variable("on", FIELD, INT),
            new_variable("the", FIELD, INT),
            new_variable("list", FIELD, INT),
            NULL
    };

    __VARIABLE* variable2[] = {
            new_variable("carolina", STATIC, CLASSNAME),
            new_variable("four", STATIC, CLASSNAME),
            NULL
    };

    __VARIABLE** variables[] = {
            variable1, variable2
    };

    return test_symbols("table/tabletests", variables, 2, compile_classvardec);
}

static unsigned int test_local_sytable(void)
{
   __VARIABLE* vars1[] = {
           new_variable("fine", LOCAL, BOOLEAN),
           NULL
   };

   __VARIABLE** variables[] = {
           vars1
   };

   return test_symbols("table/locals", variables, 1, compile_vardec);
}

static unsigned int test_parameter_stable(void)
{
    __VARIABLE* vars1[] = {
        new_variable("a", ARGUMENT, INT),
        NULL
    };

    __VARIABLE** variables[] = {
            vars1
    };

    return test_symbols("table/parameters", variables, 1, compile_parameterlist);

}

unsigned int test_tableparser(void)
{
    unsigned int (*tests[]) (void) = {
        test_vm_code,
        test_symbol_table,
        test_local_sytable
    };

    return test(tests, 3);
}
