/**
*
*       Test the table module for the Davi Compiler Collection (DCC)
*       (c) 2021 Davi Nakamura Cardoso
*
*/

#include <stdio.h>
#include <table/table.h>
#include <utils/tests.h>

static unsigned int test_new_table(void)
{
    unsigned int status;
    TABLE* t;

    t = new_table("chain", "Chain", CLASS_TYPE, ARGUMENT, 0);

    status = t != NULL;

    free(t->name);
    free(t->type_name);
    free(t);

    return status;
}

static unsigned int test_segfault_intable(void)
{
    TABLE* t = NULL;

    t = new_table(NULL, NULL, INTEGER, ARGUMENT, 0);
    release_table(&t);

    return 1;
}



unsigned int test_table(void)
{
    unsigned int (*tests[]) (void) = {
        test_new_table,
        test_segfault_intable
    };

    return test(tests, 2);
}
