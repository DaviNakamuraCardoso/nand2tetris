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
    char character;

    t = get_next_token(c->source);
    rollback(c->source);

    if (t->type != IMPLEMENTED_SYMBOL)
    {
        release_token(&t);
        return 0;
    }

    character = *(t->content);
    if (character != ')') compile_symbol(c, t->content);
    release_token(&t);

    return (character == ',');

}

void compile_class(CODE* c)
{

    /**
    *       <class> ::= class <className> { <classvardec>* <subroutinedec>* }
    */
    TOKEN* next;

    opentag(c, "class");
    compile_keyword(c, "class");
    compile_identifier(c);
    compile_symbol(c, "{");

    next = get_next_token(c->source);
    rollback(c->source);

    while (strcmp(next->content, "field") == 0 ||
        strcmp(next->content, "static") == 0) {
        compile_classvardec(c);
        release_token(&next);
        next = get_next_token(c->source);
        rollback(c->source);
    }

    release_token(&next);
    next = get_next_token(c->source);
    rollback(c->source);

    while (strcmp(next->content, "}") != 0)
    {
        compile_subroutinedec(c);
        release_token(&next);
        next = get_next_token(c->source);
        rollback(c->source);
    }
    release_token(&next);

    compile_symbol(c, "}");

    closetag(c, "class");
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
        compile_identifier(c);
        release_token(&next);

    } while (compile_comma(c));

    closetag(c, "varDec");
}

void compile_subroutinebody(CODE* c)
{
    /*
    *     <subroutinebody> ::= {<vardec>* <statements> }
    */

    TOKEN* next;
    opentag(c, "subroutineBody");

    compile_symbol(c, "{");

    next = get_next_token(c->source);
    while (strcmp(next->content, "var") == 0)
    {
        release_token(&next);
        rollback(c->source);
        compile_vardec(c);
        next = get_next_token(c->source);
    }

    rollback(c->source);

    compile_statements(c);

    compile_symbol(c, "}");
    closetag(c, "subroutineBody");
}

void compile_function_predec(CODE* c)
{
    TOKEN* t;
    char* predecs[] = {
        "method",
        "function",
        "constructor",
        NULL
    };

    t = get_next_token(c->source);
    rollback(c->source);

    if (t->type != KEYWORD)
    {
        release_token(&t);
        return;
    }

    for (int i = 0; predecs[i] != NULL; i++)
    {
        if (strcmp(predecs[i], t->content) == 0)
        {
            compile_keyword(c, predecs[i]);
            release_token(&t);
            return;
        }
    }


    return;
}


void compile_classfield(CODE* c)
{
    char* fieldtypes[] = {
        "static",
        "field",
        NULL

    };
    TOKEN* t = get_next_token(c->source);
    rollback(c->source);

    for (int i = 0; fieldtypes[i] != NULL; i++)
    {
        if (strcmp(fieldtypes[i], t->content) == 0)
        {
            compile_keyword(c, fieldtypes[i]);
            release_token(&t);
            return;
        }
    }

    return;
}

void compile_classvardec(CODE* c)
{
    /**
    *      <classvardec> ::= (static | field) <type> <varname> (, <varname>)* ;
    */

    opentag(c, "classVarDec");

    compile_classfield(c);
    compile_type(c);

    do {
        compile_identifier(c);

    } while (compile_comma(c));

    closetag(c, "classVarDec");

    return;
}

void compile_function_type(CODE* c)
{
    TOKEN* t;

    t = get_next_token(c->source);

    rollback(c->source);


    if (strcmp(t->content, "void") == 0)
    {
        compile_keyword(c, "void");
        release_token(&t);
        return;
    }

    compile_type(c);
    release_token(&t);
}
void compile_subroutinedec(CODE* c)
{
    /**
    *   <subroutinedec> ::= (constructor | function | method) (void | <type>) <subroutineName>
    *   <parameterList> <subroutineBody>
    */
    opentag(c, "subroutineDec");

    compile_function_predec(c);
    compile_function_type(c);
    compile_identifier(c);
    compile_parameterlist(c);
    compile_subroutinebody(c);

    closetag(c, "subroutineDec");
    return;

}

void compile_parameterlist(CODE* c)
{

    /**
    *   <parameterlist> ::= (<type> <varname> (, <type> <varname>)*)
    */
    TOKEN* t;

    compile_symbol(c, "(");
    opentag(c, "parameterList");

    t = get_next_token(c->source);
    rollback(c->source);

    if (strcmp(t->content, ")") == 0)
    {
        goto end_of_compile_paremter_list_fn;
    }

    do {
        compile_type(c);
        compile_identifier(c);

    } while (compile_comma(c));

    end_of_compile_paremter_list_fn:
    {
        release_token(&t);
        closetag(c, "parameterList");
        compile_symbol(c, ")");
        return;

    }
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
