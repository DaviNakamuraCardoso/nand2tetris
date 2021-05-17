/*
*   Test suite for the Davi Compiler Collection (DCC)
*   (c) 2021 Davi Nakamura Cardoso
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tests.h>
#include <tokenizer/test_tokens.h>
#include <tokenizer/test_precomp.h>
#include <tokenizer/test_reader.h>
#include <tokenizer/test_cleaner.h>
#include <tokenizer/test_parser.h>

#define BASE_DIR ".."

int main(void)
{
    char buff[200];
    int test_num, i;

    printf("Starting tests...\n");

    unsigned int (*test_functions[]) (void) = {
        test_compilation,
        test_tokenizer,
        test_precomp,
        test_reader,
        test_memory_leaks,
        test_cleaner,
        test_parser
    };


    test_num = 7;

    for (i = 0; i < test_num; i++)
    {
        if (!test_functions[i]())
        {
            printf("Fail on test %i\n", i);
            return 1;
        }
    }

    printf("All tests passed.\n");


    return 0;
}

unsigned int test_compilation(void)
{
    char buff[200], *program_name;
    int status;

    program_name = "dcc";

    sprintf(buff, "cd .. && make \"%s\"", program_name);

    status = system(buff);

    return (status == 0);
}

unsigned int test_memory_leaks(void)
{
    int status;
    char buff[200], *program_name;
    program_name = "./dcc";

    sprintf(buff, "cd .. && valgrind \"%s\"", program_name);

    status = system(buff);

    return (status == 0);
}
