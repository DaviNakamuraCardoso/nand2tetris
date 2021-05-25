/*
*       Test the compile functions for the Davi Compile Collection (DCC)
*       (c) 2021 Davi Nakamura Cardoso
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utils/tests.h>
#include <tokenizer/reader.h>
#include <compengine/compile.h>

unsigned int test_compilef(void)
{
    unsigned short s, size;

    char* cmp;

    char* expected = "<keyword>class</keyword>\n\t<stringConstant>Hello, World!</stringConstant>\n";

    char* tags[] = {
        "<keyword>class</keyword>",
        "<stringConstant>Hello, World!</stringConstant>"
    };

    FILE* f = fopen("./files/compengine/compilef.xml", "w");

    size = 2;


    for (s = 0; s < size; s++)
    {
        compilef(s, tags[s], f);
    }

    fclose(f);


    cmp = get_file("./files/compengine/compilef.xml");


    if (strcmp(cmp, expected) != 0)
    {
        printf("Error in compilef function\n");
        return 0;
    }

    free(cmp);

    return 1;
}

unsigned int test_compile_symbol(void)
{
    int i = 0;
    unsigned short s, size;
    char* result, *expected, filename[300], filename2[300], filename3[300];
    FILE* target, *source;


    size = 1;
    for (s = 0; s < size; s++)
    {

        sprintf(filename, "./files/compengine/compile_symbol_%i.xml", s);
        sprintf(filename2, "./files/compengine/compile_symbol_%i_out.xml", s);
        sprintf(filename3, "./files/compengine/compile_symbol_expected_%i.xml", s);

        source = fopen(filename, "r");
        target = fopen(filename2, "w");

        CODE c = {.target=target, .source=source, .identation=&i};

        char* symbols[] = { "(", "~", "&amp;", "*", "}"};
        for (unsigned short t = 0; t < 5; t++)
        {
            if (!compile_symbol(&c, symbols[t])) printf("Wrong status\n");
        }

        fclose(source);
        fclose(target);

        expected = get_file(filename3);
        result = get_file(filename2);

        if (strcmp(expected, result) != 0)
        {
            return 0;
        }

        free(expected);
        free(result);
    }

    return 1;

}

unsigned int test_compile_keyword(void)
{
    unsigned short s, size;
    int i = 0;
    char* result, *expected;
    FILE* target, *source;

    char* keywords[] = { "class", "goto", "inline", "exotic", "dangerous"};

    source = fopen("./files/compengine/keyword.xml", "r");
    target = fopen("./files/compengine/keyword_out.xml", "w");

    CODE c = {.identation=&i, .target=target, .source=source};

    size = 5;
    for (s = 0; s < size; s++)
    {
        compile_keyword(&c, keywords[s]);
    }

    fclose(target);
    fclose(source);

    result = get_file("./files/compengine/keyword_out.xml");
    expected = get_file("./files/compengine/keyword_expected.xml");

    if (strcmp(result, expected) != 0)
    {
        printf("Error in compile_symbol %i\n", s);
        printf("Expected: %s\n", expected);
        printf("Result: %s\n", result);

        free(expected);
        free(result); 
        return 0;
    }

    free(expected);
    free(result);


    return 1;
}


unsigned int test_compile(void)
{
    unsigned int (*tests[]) (void) = {
        test_compilef,
        test_compile_symbol,
        test_compile_keyword
    };

    return test(tests, 3);
}
