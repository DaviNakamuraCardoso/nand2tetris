/**
*
*       Responsible for parsing the program structure
*       for the Davi Compiler Collection (DCC)
*       (c) 2021 Davi Nakamura Cardoso
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utils/error.h>
#include <tokenizer/tokens.h>
#include <tokenizer/cleaner.h>
#include <compengine/parser.h>
#include <compengine/compile.h>
#include <compengine/structure.h>

void handle_type(TYPE type, CODE* c, TOKEN* token);
TYPE get_content_type(char* content);

void compile_subroutinecall(CODE* c)
{
    opentag(c, "subroutineCall");

    closetag(c, "subroutineCall");
}

void compile_type(CODE *c)
{
    TOKEN* next = get_next_token(c->source);
    TYPE t;

    rollback(c->source);


    t = get_content_type(next->content);
    handle_type(t, c, next);

    release_token(&next);
    return;

}

unsigned int compile_comma(CODE* c)
{
    TOKEN* t;

    t = get_next_token(c->source);
    rollback(c->source);

    if (t->type != IMPLEMENTED_SYMBOL);

    
}



void compile_vardec(CODE* c)
{
    TOKEN* next;
    opentag(c, "varDec");

    compile_keyword(c, "var");

    compile_type(c);

    do {
        next = get_next_token(c->source);
        rollback(c->source);
        compile_varname(c);
        release_token(&next);

    } while (compile_comma(c));

    closetag(c, "varDec");
}

void handle_type(TYPE type, CODE* c, TOKEN* token)
{
    switch (type)
    {
        case INVALID_TYPE:
        {
            error("Invalid type declaration.");
        }
        case CLASSNAME:
        {
            compile_identifier(c);
            break;
        }
        default:
        {
            compile_keyword(c, token->content);
        }
    }
    return;
}

TYPE get_content_type(char* content)
{
    char* types[] = {
        "int", "char", "boolean", NULL
    };


    for (int i = 0; types[i] != NULL; i++)
    {
        if (strcmp(types[i], content) == 0)
        {
            return i;
        }
    }


    if (check_variable(content) != -1)
    {
        return CLASSNAME;
    }

    return INVALID_TYPE;
}
