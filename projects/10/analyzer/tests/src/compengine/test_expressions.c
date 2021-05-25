/**
*
*       Test the expression parsing module
*       (c) 2021 Davi Nakamura Cardoso
*/

#include <stdio.h>
#include <stdlib.h>
#include <utils/tests.h>
#include <tokenizer/reader.h>
#include <tokenizer/tokens.h>
#include <compengine/compile.h>
#include <compengine/expressions.h>

unsigned int test_compile_expressions(void)
{
    int ident = 0;
    unsigned short i, size;
    char filename[300], filename2[300], filename3[300], *result, *expected;
    FILE* t, *s;
    size = 1;

    for (i = 0; i < size; i++)
    {
        sprintf(filename, "./files/compengine/expressions/expression_%i.xml", i);
        sprintf(filename2, "./files/compengine/expressions/expression_out_%i.xml", i);
        sprintf(filename3, "./files/compengine/expressions/expression_cmp_%i.xml", i);

        s = fopen(filename, "r");
        t = fopen(filename2, "w");

        CODE c = {.target=t, .source=s, .identation=&ident};
        compile_expression(&c);

        fclose(s);
        fclose(t);


        result = get_file(filename2);
        expected = get_file(filename3);


        if (strcmp(result, expected) != 0)
        {
            printf("Error in compile expression number %i\n", i);
            printf("Expected: %s\n", expected);
            printf("Result: %s\n", result);
            free(result);
            free(expected);
            return 0;
        }

        free(result);
        free(expected);
    }

    return 1;
}


unsigned int test_expressions(void)
{
    unsigned int (*tests[]) (void) = {
        test_compile_expressions
    };

    return test(tests, 1);
}
