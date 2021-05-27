/*
*
*       Test the structure parser for the Davi Compiler Collection (DCC)
*       (c) 2021 Davi Nakamura Cardoso
*/

#include <stdio.h>
#include <stdlib.h>
#include <tokenizer/tokens.h>
#include <compengine/parser.h>
#include <compengine/compile.h>
#include <compengine/structure.h>
#include <utils/tests.h>

unsigned int test_compile_type(void)
{
    return generic_compare("type", compile_type, 3);
}


unsigned int test_structure(void)
{
    unsigned int (*tests[]) (void) = {
        test_compile_type

    };
    return test(tests, 1);
}
