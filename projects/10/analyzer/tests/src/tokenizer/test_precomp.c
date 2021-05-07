/**
*       Test the precompilation process
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tokenizer/precomp.h>

unsigned int compare_results(char** input, char** expected,
    int size, char* (*tested_function) (char*))
{
    int i;
    char* msg;

    for (i = 0; i < size; i++)
    {
        msg = tested_function(input[i]);
        if (strcmp(msg, expected[i]) != 0)
        {
            printf("Fail parsing %i.\n", i);
            printf("Input: %s\n", input[i]);
            printf("Expected: %s\n", expected[i]);
            printf("Returned: %s\n", msg);
            return 0;
        }
    }
    return 1;
}

unsigned int can_handle_whitespaces(void)
{
    int i;
    unsigned int result;

    char* messages[] = {
        "   let a = b;",
        "  do a();",
        "class Java {}",
        "",
        "   switch (card)",
        "my %wife;   "

    };

    char* expected[] = {
        "let a = b;",
        "do a();",
        "class Java {}",
        "",
        "switch (card)",
        "my %wife;   "

    };

    return (compare_results(messages, expected, 6, handle_whitespaces));
}

unsigned int can_handle_inline_comments(void)
{
    unsigned int result;

    char* msgs[] = {
        "// This is an inline comment\n",
        "// Sets a to b\nmy a = b;",
        "\ni++; // increase i by 1",
        "// Check if file is null\nbool checkIfFileIsNull(File f)\n",
        "// Assignment\na = a / b;\n",
        ""

    };

    char* expec[] = {
        "",
        "my a = b;",
        "i++; // increase i by 1",
        "bool checkIfFileIsNull(File f)\n",
        "a = a / b;\n",
        ""
    };


    return compare_results(msgs, expec, 6, handle_inline_comments);
}

unsigned int can_handle_multiple_line_comments(void)
{
    unsigned int result;

    char* msgs[] = {
        "/** This is a JavaDoc */\nclass Hello {\n",
        "/***/",
        "typedef struct _hello {",
        "HELLO**/create_hello(char* msg)\n",
        "a *= b / a * c / */(a**2)\n",
        ""
    };

    char* expected[] = {
        "\nclass Hello {\n",
        "",
        "",
        "create_hello(char* msg)\n",
        "(a**2)\n",
        ""
    };


    return compare_results(msgs, expected, 6, handle_multiple_line_comments);
}

// unsigned int doesnt_open_null_file(void)
// {

// }

unsigned int test_precomp(void)
{
    int size, i;

    unsigned int (*tests[]) (void) = {
        can_handle_whitespaces,
        can_handle_inline_comments,
        can_handle_multiple_line_comments
    };

    size = 3;

    for (i = 0; i < size; i++)
    {
        if (!tests[i]()) return 0;
    }

    return 1;

}
