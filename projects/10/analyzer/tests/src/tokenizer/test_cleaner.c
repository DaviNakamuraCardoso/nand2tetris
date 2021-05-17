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
        add_keywords_and_symbols(root, filenames[i], NULL);

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
    char** result;

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
        result = get_string_literal(string_literals[i], "\"");

        if (result[2] == NULL)
        {
            if (strcmp("", expected[i]) != 0) return 0;
            free(result[1]);
            free(result);
            continue;
        }
        if (strcmp(result[2], expected[i]) != 0)
        {
            printf("Error parsing string literals\nNumber: %i\n", i);
            printf("Expected: %s\n", expected[i]);
            printf("Result: %s\n", result[2]);
            free(result[1]);
            free(result[2]);
            return 0;
        }

        if (result != NULL)
        {
            free(result[1]);
            free(result[2]);
            free(result);
        }
    }

    return 1;
}


unsigned int test_number_literals(void)
{
    int i, size;
    char **result;

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

        result = get_number_constant(input[i], "9");

        if (result == NULL)
        {
            if (strcmp("", expected[i]) != 0) return 0;
            continue;
        }

        if (strcmp(result[2], expected[i]) != 0)
        {
            printf("Fail in test number %i\n", i);
            printf("Result: %s\n", result[2]);
            printf("Expected: %s\n", expected[i]);
            free(result[1]);
            free(result[2]);
            free(result);
            return 0;
        }

        free(result[1]);
        free(result[2]);
        free(result);

    }


    return 1;
}

unsigned int generic_keyword_test(char **input1, char **input2, char** ret1, const char* key, int size)
{

    int i, cmp1, cmp2, cmp3;
    SYMBOL* root;
    char **result;

    root = symbol_manager("../syntax");


    for (i = 0; i < size; i++)
    {
        result = handle_symbol(root, input2[i], input1[i], input2[i]);

        cmp1 = strcmp(result[0], ret1[i]);
        cmp2 = strcmp(result[1], key);
        cmp3 = strcmp(result[2], input2[i]);


        if (cmp1 != 0 || cmp2 != 0 || cmp3 != 0)
        {
            // Print results
            printf("%s\n", result[0]);
            printf("%s\n", result[1]);
            printf("%s\n", result[2]);

            // Clean up
            release_symbol(&root);
            free(result[1]);
            free(result[2]);
            free(result);
            return 0;
        }

        free(result[1]);
        free(result[2]);
        free(result);
    }

    release_symbol(&root);

    return 1;
}

unsigned int test_symbol_manager(void)
{
    int size;

    char* input1[] = {
        "- 1",
        "; let",
        "& 9",
        "NO SYMBOLS"
    };

    char* input2[] = {
        "-",
        ";",
        "&",
        ""
    };

    char* ret1[] = {
        " 1",
        " let",
        " 9",
        "NO SYMBOLS"
    };

    size = 4;

    return generic_keyword_test(input1, input2, ret1, "symbol", size);
}

unsigned int test_keywords(void)
{
    int size;


    char* input1[] = {
        "let i =",
        "var int i",
        "while ()"
    };

    char* input2[] = {
        "let",
        "var",
        "while"

    };

    char* ret1[] = {
        " i =",
        " int i",
        " ()"
    };

    size = 3;

    return generic_keyword_test(input1, input2, ret1, "keyword", size);
}

unsigned int test_string_manager(void)
{
    int size, i, ra, rb, rc;
    SYMBOL* root;
    char **result = NULL;

    char* input1[] = {
        "print \"Hellow, World\";",
        "say \"Hail!\";",
        ""
    };

    char* input2[] = {
        "\"",
        "\"",
        ""
    };

    char* ret[] = {
        ";",
        ";",

    };

    char* ret2[] = {
        "Hellow, World",
        "Hail!",
    };

    size = 2;

    root = symbol_manager("../syntax");

    for (i = 0; i < size; i++)
    {
        result = handle_symbol(root, input2[i], input1[i], input2[i]);

        if (result == NULL) continue;

        ra = strcmp(result[0], ret[i]);
        rb = strcmp(result[1], "StringConstant");
        rc = strcmp(result[2], ret2[i]);


        if (ra != 0 || rb != 0 || rc != 0)
        {
            printf("Error in comparison %i\n", i);
            printf("Result: %s\n%s\n%s\n", result[0], result[1], result[2]);
            printf("Expected: %s\n%s\n%s\n", ret[i], "StringConstant", ret2[i]);
            release_symbol(&root);
            free(result);
            return 0;
        }

        free(result[1]);
        free(result[2]);
        free(result);
    }

    release_symbol(&root);
    return 1;
}

unsigned int test_get_number_literals(void)
{
    int i, size, ca, cb, cc;
    char** result;
    SYMBOL* root;


    char* input1[] = {
        "12 is",
        "7 days",
        "40",
        "30 years old"
    };

    char* input2[] = {
        "1",
        "7",
        "4",
        "3"
    };

    char* expected[] = {
        "12",
        "7",
        "40",
        "30"
    };

    char* expected2[] = {
        " is",
        " days",
        "",
        " years old"
    };

    size = 4;

    root = symbol_manager("../syntax");

    for (i = 0; i < size; i++)
    {
        result = handle_symbol(root, input2[i], input1[i], input2[i]);

        if (result == NULL)
        {
            if (strcmp(expected2[i], "") == 0) continue;
        }

        ca = strcmp(result[0], expected2[i]);
        cb = strcmp(result[1], "integerConstant");
        cc = strcmp(result[2], expected[i]);

        if (ca != 0 || cb != 0 || cc != 0)
        {
            printf("Error in comparison %i\n", i);
            printf("%s\n%s\n%s\n", result[0], result[1], result[2]);
            free(result[1]);
            free(result[2]);
            free(result);
            release_symbol(&root);

            return 0;
        }
        free(result[1]);
        free(result[2]);
        free(result);

    }


    release_symbol(&root);
    return 1;
}

unsigned int test_get_defined_var(void)
{

}


unsigned int test_cleaner(void)
{
    int i, size;

    unsigned int (*tests[]) (void) = {
        test_keywords_from_file,
        test_get_string_literals,
        test_number_literals,
        test_symbol_manager,
        test_keywords,
        test_string_manager,
        test_get_number_literals
    };

    size = 7;

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
