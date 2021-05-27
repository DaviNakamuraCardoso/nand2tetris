/**
*
*       Test the expression parsing module
*       (c) 2021 Davi Nakamura Cardoso
*/

#include <stdio.h>
#include <stdlib.h>
#include <tokenizer/reader.h>
#include <tokenizer/tokens.h>
#include <compengine/compile.h>
#include <compengine/expressions.h>
#include <utils/tests.h>

unsigned int test_compile_expressions(void)
{
    return generic_compare("expression", compile_expression, 1);
}


unsigned int test_expressions(void)
{
    unsigned int (*tests[]) (void) = {
        test_compile_expressions
    };

    return test(tests, 1);
}
