/*
    Test the tokenizer parser module
*/

#include <stdio.h>
#include <stdlib.h>
#include <tokenizer/tokens.h>
#include <tokenizer/reader.h>
#include <tokenizer/cleaner.h>
#include <tokenizer/parser.h>


unsigned int test_write_xml(void)
{

    int size, i;
    char *file_content;
    FILE *test_file;

    test_file = fopen("files/tokenizer/test_write_xml.xml", "w");

    char** results[] = {
        // get_string_literal("\"Hello, World!\"", "\""),
        // get_number_constant("3923 Hello", "3"),

    };

    size = 2;

    for (i = 0; i < size; i++)
    {
        write_xml(results[i], test_file);
    }

    fclose(test_file);

    char expected[] = "<StringConstant>Hello, World!</StringConstant>\n<integerConstant>3923</integerConstant>\n";

    file_content = get_file("files/tokenizer/test_write_xml.xml");

    if (strcmp(expected, file_content) != 0)
    {
        printf("Error in write_xml function\n");
        printf("Result: %s\nExpected: %s\n", file_content, expected);
        return 0;
    }

    free(file_content);


    return 1;
}

unsigned int test_file_step(void)
{


}

unsigned int test_parser(void)
{
    int i, size;

    unsigned int (*tests[]) (void) = {
        test_write_xml
    };

    size = 0;

    printf("Running parser tests.\n");
    for (i = 0; i < size; i++)
    {
        if (!tests[i]())
        {
            printf("Error in test %i\n", i);
            return 0;
        }
    }
    return 1;
}
