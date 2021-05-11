/**
* Test the cleaner module from the compile tokenizer
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <tokenizer/tokens.h>
#include <tokenizer/precomp.h>
#include <tokenizer/reader.h>
#include <tokenizer/cleaner.h>


unsigned int test_keywords_from_file(void)
{
    int i, j, size, cmp_size;
    char* result;
    SYMBOL* root;

    char* filenames[] = {
        "files/tokenizer/03.txt",
        "files/tokenizer/04.txt",
        "files/tokenizer/05.txt",
    };

    char* f[] = {"foo", "bar", "baz"};
    char* f2[] = {",", "goto", "-"};
    char* f3[] = {"my", "our", "bless"};

    char** expected[] = {
        f,
        f2,
        f3

    };

    size = 3;
    cmp_size = 3;

    root = create_symbol();
    for (i = 0; i < size; i++)
    {
        add_keywords_and_symbols(root, filenames[i]);

        for (j = 0; j < cmp_size; j++)
        {
            if (!search_symbol(root, expected[i][j]))
            {
                printf("Fail in test %i, %i\n", i, j);
                printf("%s was supposed to be in tree\n", expected[i][j]);
                return 0;
            }
        }
    }

    release_symbol(&root);
    return 1;

}


unsigned int test_get_string_literals(void)
{
    int i, size;
    char* result;

    char* string_literals[] = {
        "my $phrase = \"Howdy, World!\";",
        "printf(\"Hello, World\");",
        "print 'Howdy, world';",
        "",
        "\"\"",
        "printf(\"Then David said: \"Really good question\"\n\")"
    };

    char* expected[] = {
        "Howdy, World!",
        "Hello, World",
        "",
        "",
        "",
        "Then David said: "
    };

    size = 6;

    for (i = 0; i < size; i++)
    {
        result = get_string_literal(string_literals[i]);

        if (result == NULL)
        {
            if (strcmp("", expected[i]) != 0) return 0;
            continue;
        }
        if (strcmp(result, expected[i]) != 0)
        {
            printf("Error parsing string literals\nNumber: %i\n", i);
            printf("Expected: %s\n", expected[i]);
            printf("Result: %s\n", result);
            return 0;
        }

        if (result != NULL) free(result);

    }

    return 1;
}

unsigned int test_number_literals(void)
{
    int i, size;
    char *result;

    char* input[] = {
        "12",
        "7",
        "for (i = 0; i < size; i++)\n",
        "my $phrase = 'No numbers here\n';"
    };

    char* expected[] = {
        "12",
        "7",
        "0",
        ""
    };

    size = 4;

    for (i = 0; i < size; i++)
    {

        result = get_number_constant(input[i]);
        
        if (result == NULL)
        {
            if (strcmp("", expected[i]) != 0) return 0;
            continue;
        }

        if (strcmp(result, expected[i]) != 0)
        {
            printf("Fail in test number %i\n", i);
            printf("Result: %s\n", result);
            printf("Expected: %s\n", expected[i]);
            free(result);
            return 0;
        }

        free(result);
    }

    return 1;
}


unsigned int test_cleaner(void)
{
    int i, size;

    unsigned int (*tests[]) (void) = {
        test_keywords_from_file,
        test_get_string_literals,
        test_number_literals
    };

    size = 3;

    for (i = 0; i < size; i++)
    {
        if (!tests[i]())
        {
            printf("Error in cleaner test %i\n", i);
            return 0;
        }
    }

    return 1;

}
