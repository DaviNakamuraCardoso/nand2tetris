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
    FILE *source, *target, *cmp;

    for (s = 0; s < size; s++)
    {
        sprintf(filename, "./files/compengine/%s/%i.xml", expression, s);
        sprintf(filename2, "./files/compengine/%s/out_%i.xml", expression,s);
        sprintf(filename3, "./files/compengine/%s/cmp_%i.xml", expression,s);

        source = fopen(filename, "r");
        target = fopen(filename2, "w");
        // cmp = fopen(filename3, "w");
        i = 0;
        CODE c = {.identation=&i, .target=target, .source=source};

        tested(&c);

        fclose(source);
        fclose(target);

        result = get_file(filename2);
        expected = get_file(filename3);

        // fprintf(cmp, "%s", result);

        // fclose(cmp);

        if (strcmp(result, expected) != 0)
        {
            printf("Error in %s number %i\n", expression, s);
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


unsigned int test_compile_implemented(const char* name, unsigned int (*function) (CODE*, char*), int size)
{
    unsigned short s;
    int i = 0;
    char* result, *expected, filename[300], filename2[300], filename3[300];
    FILE* target, *source, *cmp;


    for (s = 0; s < size; s++)
    {
        sprintf(filename,  "./files/compengine/%s/%i.xml", name, s);
        sprintf(filename2, "./files/compengine/%s/%i_out.xml", name, s);
        sprintf(filename3, "./files/compengine/%s/%i_cmp.xml", name, s);

        source = fopen(filename, "r");
        target = fopen(filename2, "w");
        // cmp = fopen(filename3, "w");

        CODE c = {.identation=&i, .target=target, .source=source};

        function(&c, "bing");

        fclose(target);
        fclose(source);

        result = get_file(filename2);
        expected = get_file(filename3);

        // fprintf(cmp, "%s", result);

        // fclose(cmp);
        if (strcmp(result, expected) != 0)
        {
            printf("Error in compile_symbol %i\n", s);
            printf("Expected: %s\n", expected);
            printf("Result: %s\n", result);

            free(expected);
            free(result);
            return 0;
        }

        // free(expected);
        free(result);

    }

    return 1;
}
