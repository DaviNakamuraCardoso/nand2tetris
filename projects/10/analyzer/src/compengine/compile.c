/*
*
*    A set of generic compile functions used by all compilation engine modules
*    (c) 2021 Davi Nakamura Cardoso
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tokenizer/tokens.h>
#include <compengine/parser.h>
#include <compengine/compile.h>


// Private function putident
void putident(int ident, FILE* f);
void compile_variable(CODE* c, TOKEN* t);


void compilef(int identation, char* text, FILE* target)
{
    putident(identation, target);
    fprintf(target, "%s\n", text);
    return;
}


void dec(int *identation)
{
    *identation = *identation - 1;
    return;
}


void inc(int *identation)
{
    *identation = *identation + 1;
    return;
}


void putident(int ident, FILE* f)
{
    for (int i = 0; i < ident; i++) { fputc('\t', f); }
    return;
}

void assert_type(TOKEN_TYPE a, TOKEN_TYPE b, int* status)
{
    if (a != b)
    {
        *status = 0;
    }
    return;
}

void assert_content(char* a, char* b, int* status)
{
    if (strcmp(a, b) != 0)
    {
        *status = 0;
    }
    return;
}

void compile_symbol_tag(int *identation, char* content, FILE* target)
{
    char tag[500];

    sprintf(tag, "<symbol>%s</symbol>", content);
    compilef(*identation, tag, target);
    return;
}

void compile_tag(CODE* c, char* content, char* tagname)
{
    char tag[1000];

    sprintf(tag, "<%s>%s</%s>", tagname, content, tagname);
    compilef(*(c->identation), tag, c->target);
    return;

}

unsigned int compile_implemented(CODE* c, char* content, char* tagname, TOKEN_TYPE type)
{
    TOKEN* token = get_next_token(c->source);
    unsigned int status = 1;

    assert_type(token->type, type, &status);
    assert_content(token->content, content, &status);

    if (!status)
    {
        release_token(&token);
        return 0;
    }

    compile_tag(c, content, tagname);
    release_token(&token);

    return 1;

}


unsigned int compile_symbol(CODE* c, char* symbol)
{
    return compile_implemented(c, symbol, "symbol", IMPLEMENTED_SYMBOL);
}

unsigned int compile_keyword(CODE* c, char* keyword)
{
    return compile_implemented(c, keyword, "keyword", KEYWORD);
}

unsigned int compile_identifier(CODE* c)
{
    int status = 1;
    TOKEN* token;

    token = get_next_token(c->source);

    assert_type(token->type, VARIABLE, &status);

    if (status)
    {
        compile_variable(c, token);
    }

    release_token(&token);
    return status;
}

void compile_string(CODE* c)
{
    TOKEN* token = get_next_token(c->source);

}

void compile_variable(CODE* c, TOKEN* t)
{
    char tag[500];

    sprintf(tag, "<identifier>%s</identifier>", t->content);
    compilef(*(c->identation), tag, c->target);

    return;
}

void opentag(CODE* c, const char* tagname)
{
    char tag[500];
    sprintf(tag, "<%s>", tagname);

    compilef(*(c->identation), tag, c->target);

    inc(c->identation);

    return;
}

void closetag(CODE* c, const char* tagname)
{
    char tag[500];
    sprintf(tag, "</%s>", tagname);

    dec(c->identation);

    compilef(*(c->identation), tag, c->target);

    return;
}
