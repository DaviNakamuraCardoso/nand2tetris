/*
    Test the tokenizer parser module
*/

#include <stdio.h>
#include <stdlib.h>
#include <tokenizer/tokens.h>
#include <tokenizer/reader.h>
#include <tokenizer/cleaner.h>
#include <tokenizer/parser.h>

unsigned int test_types_table(void)
{
    unsigned short s, size;
    SYMBOL* types_table;

    char* compare[] = {
        "while",
        "if",
        "&",
        "{",
        "hi"
    };

    TOKEN_TYPE types[] = {
        KEYWORD, KEYWORD, IMPLEMENTED_SYMBOL, IMPLEMENTED_SYMBOL, -1
    };

    size = 5;

    types_table = new_types_table();

    for (s = 0; s < size; s++)
    {
        if (get_token_type(types_table, compare[s]) != types[s])
        {
            printf("Error in types_table, comparison %i\n", s);
            printf("Result: %i\n", get_token_type(types_table, compare[s]));
            printf("Expected: %i\n", types[s]);
            release_symbol(&types_table);
            return 0;
        }
    }

    release_symbol(&types_table);
    return 1;
}

unsigned int test_get_type(void)
{
    unsigned short s, size;

    char* tokens[] = { "while", "if", "else", "&", "-", "*", "variable",
    "game", "game_mode", "\"Hello, World\"", "\"Hi\"", "\"Tetris\"","929", "10", "29" };

    TOKEN_TYPE types[] = {
        KEYWORD, KEYWORD, KEYWORD,
        IMPLEMENTED_SYMBOL, IMPLEMENTED_SYMBOL, IMPLEMENTED_SYMBOL,
        VARIABLE, VARIABLE, VARIABLE,
        STRING_LITERAL, STRING_LITERAL, STRING_LITERAL,
        NUMBER_CONSTANT, NUMBER_CONSTANT, NUMBER_CONSTANT

    };

    SYMBOL* root;

    root = new_types_table();

    size = 15;

    for (s = 0; s < size; s++)
    {
        if (get_type(root, tokens[s]) != types[s])
        {
            printf("Error in get_type function, test %i\n", s);
            printf("Result: %i\n", get_type(root, tokens[s]));
            printf("Expected: %i\n", types[s]);
            release_symbol(&root);
            return 0;
        }
    }

    release_symbol(&root);

    return 1;
}

unsigned int test_get_tag(void)
{
    unsigned short s, size;
    char* result;

    TOKEN_TYPE input[] = {
        STRING_LITERAL,
        NUMBER_CONSTANT,
        VARIABLE,
        KEYWORD,
        IMPLEMENTED_SYMBOL
    };

    char* tags[] = {
        "StringConstant",
        "numberConstant",
        "variable",
        "keyword",
        "symbol"
    };

    size = 5;
    for (s = 0; s < size; s++)
    {
        result = get_tag(input[s]);

        if (strcmp(result, tags[s]) != 0)
        {
            printf("Error in get_tag number %i\n", s);
            printf("Result: %s\n", result);
            printf("Expected: %s\n", tags[s]);
            free(result);

            return 0;
        }
        
        free(result);

    }

    return 1;
}

unsigned int test_parser(void)
{
    int i, size;

    unsigned int (*tests[]) (void) = {
        test_types_table,
        test_get_type,
        test_get_tag
    };

    size = 3;

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
