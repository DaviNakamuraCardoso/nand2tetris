/**
*
*       Tests for the Compilation Engine Parser
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tokenizer/tokens.h>
#include <compengine/parser.h>


unsigned int test_new_token(void)
{
    unsigned short s, size;
    TOKEN* token;

    char* contents[] = {
        "",
        "class",
        "&",
        "Hello, World!",
        "3292",
        "camel"
    };

    TOKEN_TYPE types[] = {
        INVALID,
        KEYWORD,
        IMPLEMENTED_SYMBOL,
        STRING_LITERAL,
        NUMBER_CONSTANT,
        VARIABLE

    };

    size = 6;

    for (s = 0; s < size; s++)
    {
        token = new_token(contents[s], types[s]);

        if (token == NULL)
        {
            printf("Fail in new_token test %i\n", s);
            printf("New struct is NULL.\n");
            return 0;
        }

        if (token->type != types[s])
        {
            printf("Fail in new_token test %i\n", s);
            printf("Wrong TOKEN_TYPE assigned to new element.\n");
            return 0;
        }

        if (strcmp(token->content, contents[s]) != 0)
        {
            printf("Fail in new_token test %i\n", s);
            printf("Wrong content assigned to new element.\n");
            return 0;
        }

        release_token(&token);
    }
    return 1;
}

unsigned int test_release_token_compengine(void)
{
    unsigned short s, size;
    TOKEN* tokens[500];

    size = 500;

    for (s = 0; s < size; s++)
    {
        tokens[s] = new_token("Hello", STRING_LITERAL);
    }

    for (s = 0; s < size; s++)
    {
        release_token(&tokens[s]);
    }

    return 1;

}

unsigned int test_parse_token_compengine(void)
{
    unsigned short s, size;
    TOKEN* token;

    char* tags[] = {
        "<symbol>(</symbol>",
        "<keyword>my</keyword>",
        "<stringConstant>Hello, World</stringConstant>",
        "<identifier>hello</identifier>",
        "<integerConstant>39</integerConstant>"
    };

    char* contents[] = {
        "(",
        "my",
        "Hello, World",
        "hello",
        "39"
    };

    TOKEN_TYPE types[] = {
        IMPLEMENTED_SYMBOL,
        KEYWORD,
        STRING_LITERAL,
        VARIABLE,
        NUMBER_CONSTANT
    };

    size = 5;

    for (s = 0; s < size; s++)
    {
        token = parse_token(tags[s]);

        if (token->type != types[s])
        {
            printf("Wrong type\n");
            return 0;
        }

        if (strcmp(token->content, contents[s]) != 0)
        {
            printf("Wrong content.\n");
            printf("Result: %s\n", token->content);
            printf("Expected: %s\n", contents[s]);
            return 0;
        }

        release_token(&token);
    }
}


unsigned int test_compparser(void)
{
    unsigned short s, size;

    unsigned int (*tests[]) (void) = {
        test_new_token,
        test_release_token_compengine,
        test_parse_token_compengine
    };

    size = 3;

    for (s = 0; s < size; s++)
    {
        if (!tests[s]())
        {
            printf("Fail in submodule test %i\n", s);
            return 0;
        }

    }
    return 1;
}
