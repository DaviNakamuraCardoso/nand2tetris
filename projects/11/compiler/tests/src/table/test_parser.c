/**
*
*       Test the parser module for tables
*       (c) 2021 Davi Nakamura Cardoso
*/

#include <stdio.h>
#include <stdlib.h>
#include <table/table.h>
#include <table/parser.h>
#include <utils/tests.h>

static unsigned int test_vm_code(void)
{
    TABLE* t = new_table();
    __VARIABLE* v = new_variable("l", STATIC, INTEGER);
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

unsigned int test_tableparser(void)
{
    unsigned int (*tests[]) (void) = {
        test_vm_code
    };

    return test(tests, 1);
}
