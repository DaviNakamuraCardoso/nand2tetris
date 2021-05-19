/**
*       Tests for the token module
*/


#include <stdio.h>
#include <stdlib.h>
#include <tokenizer/tokens.h>

unsigned int test_create_token(void)
{
    SYMBOL* s;

    s = new_symbol();

    if (s == NULL) return 0;
    free(s);
    return 1;
}

unsigned int test_add_word(void)
{
    short size = 3;

    char* inputs[] = {
        "hello",
        "goto",
        "say"
    };

    SYMBOL* root = new_symbol();


    for (short s = 0; s < size; s++)
    {
        add_symbol(root, inputs[s]);
        if (!search_symbol(root, inputs[s]))
        {
            release_symbol(&root);
            return 0;
        }
    }

    release_symbol(&root);

    return 1;
}

unsigned int test_search_words_that_arent_in_tree(void)
{
    short s, size;

    char* in_tree[] = {
        "goto",
        "say",
        "use"
    };

    char* not_in_tree[] = {
        "gotoa",
        "sa",
        "u"
    };

    SYMBOL* root;

    size = 3;

    root = new_symbol();

    for (s = 0; s < size; s++)
    {
        add_symbol(root, in_tree[s]);
    }

    for (s = 0; s < size; s++)
    {
        if (search_symbol(root, not_in_tree[s]))
        {
            printf("%s shouldn't be in tree.\n", not_in_tree[s]);
            release_symbol(&root);
            return 0;
        }
    }

    release_symbol(&root);
    return 1;
}

unsigned int test_release_token(void)
{
    SYMBOL* symbols[] = {NULL, new_symbol(), new_symbol()};

    for (int i = 0; i < 3; i++)
    {
        release_symbol(&symbols[i]);

        if (symbols[i] != NULL) return 0;
    }

    return 1;
}

unsigned int test_get_one_char(void)
{
    short size = 3;

    char* characters[] = {
        "$hello",
        "&hello",
        "(while"
    };

    char* symbols[] = {
        "$",
        "&",
        "("
    };

    SYMBOL* root = new_symbol();

    for (short s = 0; s < size; s++)
    {
        add_symbol(root, symbols[s]);
        if (!search_one_char(root, characters[s]))
        {
            release_symbol(&root);
            return 0;
        }
    }

    release_symbol(&root);
    return 1;
}


unsigned int test_add_symbols_from_file(void)
{
    unsigned short s, t, size;
    SYMBOL* root;

    char* file1[] = { "goto", "while", "int", "char", "short" };

    char* file2[] = { "class", "extends", "private", "public", "static" };

    char* file3[] = { "my", "our", "package", "say", "strict" };

    char** files[] = {file1, file2, file3};

    size = 1;
    for (s = 0; s < size; s++)
    {
        root = new_symbol();

        char filename[200];
        sprintf(filename, "files/tokenizer/symbols_%i.csv", s);

        add_symbols_from_file(root, filename);

        for (t = 0; t < 5; t++)
        {
            if (!search_symbol(root, files[s][t]))
            {
                printf("%s should be in the root.\n", files[s][t]);
                release_symbol(&root);
                return 0;
            }
        }

        release_symbol(&root);
    }

    return 1;
}

unsigned int test_tokens(void)
{
    unsigned short size, i;

    unsigned int (*tests[]) (void) = {
        test_create_token,
        test_release_token,
        test_add_word,
        test_search_words_that_arent_in_tree,
        test_get_one_char,
        test_add_symbols_from_file
    };

    size = 6;

    for (i = 0; i < size; i++)
    {
        if (!tests[i]())
        {
            printf("Fail in test %i\n", i);
            return 0;
        }
    }
    return 1;
}
