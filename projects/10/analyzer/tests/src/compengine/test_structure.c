/*
*
*       Test the structure parser for the Davi Compiler Collection (DCC)
*       (c) 2021 Davi Nakamura Cardoso
*/

#include <stdio.h>
#include <stdlib.h>
#include <utils/tests.h>
#include <tokenizer/tokens.h>
#include <compengine/parser.h>
#include <compengine/compile.h>
#include <compengine/structure.h>


unsigned int test_compile_varname(void)
{
    return 1; 
}

unsigned int test_structure(void)
{
    unsigned int (*tests[]) (void) = {

    };
    return test(tests, 0);
}
