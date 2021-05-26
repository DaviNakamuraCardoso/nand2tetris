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

unsigned int generic_compare(const char* expression, void (*tested) (CODE*), unsigned short size)
{
    unsigned short s;
    int i = 0;
    char filename[200], filename2[200], filename3[200], *result, *expected;
    FILE *source, *target;

    for (s = 0; s < size; s++)
    {
        sprintf(filename, "./files/compengine/%s/%s_%i.xml", expression, expression, s);
        sprintf(filename2, "./files/compengine/%s/%s_out_%i.xml", expression, expression,s);
        sprintf(filename3, "./files/compengine/%s/%s_cmp_%i.xml", expression, expression,s);

        source = fopen(filename, "r");
        target = fopen(filename2, "w");
        i = 0;
        CODE c = {.identation=&i, .target=target, .source=source};

        tested(&c);

        fclose(source);
        fclose(target);

        result = get_file(filename2);
        expected = get_file(filename3);

        if (strcmp(result, expected) != 0)
        {
            printf("Error in compile_while number %i\n", s);
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
