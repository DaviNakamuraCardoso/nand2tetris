/*
*
*       XML Parser source code for the Davi Compiler Collection (DCC)
*       (c) 2021 Davi Nakamura Cardoso
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tokenizer/tokens.h>
#include <compengine/parser.h>


TOKEN* new_token(char* content, TOKEN_TYPE type)
{
    TOKEN* token;

    token = malloc(sizeof(TOKEN));

    token->type = type;
    token->content = strdup(content);

    return token;
}

TOKEN_TYPE get_token_type_from_tag(char* tagname)
{
    switch (tagname[0]) {
        case 's':
            switch (tagname[1]) {
                case 'y': return IMPLEMENTED_SYMBOL;
                case 't': return STRING_LITERAL;
            }
        case 'k':
            return KEYWORD;
        case 'i':
            switch (tagname[1]) {
                case 'd':
                    return VARIABLE;
                case 'n':
                    return NUMBER_CONSTANT;
            }
    }

    return INVALID;
}


TOKEN* parse_token(char* xml)
{
    char *content, *last, *buffer;
    TOKEN_TYPE type;
    TOKEN* t;

    type = get_token_type_from_tag(xml+1);

    buffer = strdup(xml);
    content = strchr(buffer, '>') + 1;
    last = strchr(content, '<');
    *last = '\0';

    /*
                 content
        buffer/
        |    |
        v    v
        <tag>example</tag>
         ^          ^
         |          |
         buffer+1   \
        (xml+1)    last
    */

    t = new_token(content, type);

    free(buffer);

    return t;

}


void release_token(TOKEN** tokenptr)
{
    free((*tokenptr)->content);
    free(*tokenptr);
    *tokenptr = NULL;
    return;
}