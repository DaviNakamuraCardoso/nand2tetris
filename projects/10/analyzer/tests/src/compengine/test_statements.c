/*
*      Test for the statements module from the Davi Compiler Collection (DCC)
*      (c) 2021 Davi Nakamura Cardoso
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <utils/tests.h>
#include <tokenizer/reader.h>
#include <compengine/compile.h>
#include <compengine/statements.h>


unsigned int test_while(void)
{
    unsigned short s, size;
    int i = 0;
    char filename[200], filename2[200], filename3[200], *result, *expected;
    FILE *source, *target;

    size = 1;
    for (s = 0; s < size; s++)
    {
        sprintf(filename, "./files/compengine/while_%i.xml", s);
        sprintf(filename2, "./files/compengine/while_%i_out.xml", s);
        sprintf(filename3, "./files/compengine/while_%i_cmp.xml", s);

        source = fopen(filename, "r");
        target = fopen(filename2, "w");
        i = 0;
        CODE c = {.identation=&i, .target=target, .source=source};

        compile_while(&c);

        fclose(source);
        fclose(target);

        result = get_file("./files/compengine/while_0_out.xml");
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


unsigned int test_statements(void)
{

    unsigned int (*tests[]) (void) = {
        test_while
    };


    return test(tests, 1);
}
