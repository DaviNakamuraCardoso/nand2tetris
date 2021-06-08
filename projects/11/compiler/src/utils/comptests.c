#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <compengine/compile.h>
#include <tokenizer/reader.h>


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
        CODE c = {.identation=&i, .target=target, .source=source, .table=NULL};

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

unsigned int analyzer_test(const char* name, void (*function) (char*), unsigned int size)
{
    char filename[300], filename2[300], filename3[300], *result, *expected;

    for (short i = 0; i < size; i++)
    {
        sprintf(filename,  "./files/compengine/%s/%i.jack", name, i);
        sprintf(filename2, "./files/compengine/%s/%i.xml", name, i);
        sprintf(filename3, "./files/compengine/%s/%i.cmp", name, i);

        function(filename);


        result = get_file(filename2);
        expected = get_file(filename3);

        if (strcmp(result, expected) != 0)
        {
            printf("Result: %s\n", result);
            printf("Expected: %s\n", expected);
            return 0;
        }

        free(result);
        free(expected);


    }
    return 1;
}
