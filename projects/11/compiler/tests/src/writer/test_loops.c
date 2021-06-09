/**
*
*
*       Test the loop writer
*
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <utils/tests.h>
#include <writer/loops.h>


static unsigned int test_while_loop(void)
{
    return 1;
}


unsigned int test_loops(void)
{

    unsigned int (*tests[]) (void) = {
        test_while_loop
    };

    return test(tests, 1);
}
