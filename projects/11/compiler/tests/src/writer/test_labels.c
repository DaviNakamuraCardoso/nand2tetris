/**
*
*           Test the writer module for the Compiler
*           (c) 2021 Davi Nakamura Cardoso
*
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <writer/labels.h>
#include <utils/tests.h>


static unsigned int test_label_creation(void)
{
    return 1;
}

unsigned int test_labels(void)
{
    unsigned int (*tests[]) (void) = {
        test_label_creation
    };

    return test(tests, 1);
}
