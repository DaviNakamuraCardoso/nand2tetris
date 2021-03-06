/*
*       Test the compile functions for the Davi Compile Collection (DCC)
*       (c) 2021 Davi Nakamura Cardoso
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tokenizer/reader.h>
#include <tokenizer/tokens.h>
#include <compengine/parser.h>
#include <compengine/compile.h>
#include <utils/tests.h>

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
    return test_compile_implemented("symbol", compile_symbol, 3);

}

unsigned int test_compile_keyword(void)
{
    return test_compile_implemented("keyword", compile_keyword, 3);
}

unsigned int test_compile_identifier(void)
{
    return generic_compare("identifier", compile_identifier, 1);
}

unsigned int test_compile(void)
{
    unsigned int (*tests[]) (void) = {
        test_compilef,
        test_compile_symbol,
        test_compile_keyword,
        test_compile_identifier
    };

    return test(tests, 4);
}
