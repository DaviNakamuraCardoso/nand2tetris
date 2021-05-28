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
    return generic_compare("expression", compile_expression, 4);
}

unsigned int test_compile_keywordconstant(void)
{
    return generic_compare("keywordconstant", compile_keywordconstant, 3);
}

unsigned int test_compile_unaryop(void)
{
    return generic_compare("unaryop", compile_unaryop, 3);
}

unsigned int test_compile_op(void)
{
    return generic_compare("op", compile_op, 3);
}


unsigned int test_expressions(void)
{
    unsigned int (*tests[]) (void) = {
        test_compile_expressions,
        test_compile_keywordconstant,
        test_compile_unaryop,
        test_compile_op,

    };

    return test(tests, 4);
}
