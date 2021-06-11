/**
*
*
*       Test assignment generation
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <compengine/compile.h>
#include <writer/assignments.h>
#include <utils/tests.h>
#include <utils/writertests.h>

static unsigned int test_write_stack_cmd(char* cmd, void (*tested) (CODE*, char*))
{

    char path[200];

    char* vars[] = {
        "hello", "f", NULL
    };

    char** words[] = {
        vars, NULL
    };

    TABLE* t = new_table("Hello");

    add_var(t, "hello", NULL, STATIC, INT);
    add_var(t, "f", NULL, LOCAL, CHAR);

    sprintf(path, "writer/%s", cmd);

    return writer_test(path, words, tested, t);
}

static unsigned int test_write_pop(void)
{
    return test_write_stack_cmd("pop", write_pop);
}

static unsigned int test_write_push(void)
{
    return test_write_stack_cmd("push", write_push);
}

unsigned int test_assignments(void)
{
    unsigned int (*tests[]) (void) = {
        test_write_pop,
        test_write_push
    };

    return test(tests, 2);
}
