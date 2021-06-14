/**
*
*
*       Test the functions writer
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <compengine/compile.h>
#include <compengine/expressions.h>
#include <utils/tests.h>
#include <utils/writertests.h>


static unsigned int test_write_call(void)
{
    TABLE* t = new_table("Main");
    add_var(t, "a", "Paddle", LOCAL, CLASSNAME);
    add_var(t, "this", "Ball", ARGUMENT, CLASSNAME);

    return writer_compare("writer/call", compile_subroutinecall, 2, t);
}

unsigned int test_functions(void)
{
    unsigned int (*tests[]) (void) = {
        test_write_call
    };

    return test(tests, 1);
}
