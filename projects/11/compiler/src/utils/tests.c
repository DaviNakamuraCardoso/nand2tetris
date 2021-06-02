/*
*
*       A Collection of generic test functions
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tokenizer/reader.h>
#include <tokenizer/tokens.h>
#include <compengine/compile.h>

unsigned int test(unsigned int (*tests[]) (void), unsigned short size)
{
    unsigned short s;

    for (s = 0; s < size; s++)
    {
        if (!tests[s]())
        {
            printf("Failure in module test number %i\n", s);
            return 0;
        }
    }

    return 1;
    
}
