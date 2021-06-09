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
#include <compengine/compile.h>
#include <tokenizer/cleaner.h>
#include <compengine/parser.h>
#include <compengine/statements.h>
#include <compengine/structure.h>

void handle_type(TYPE type, CODE* c, TOKEN* token);
TYPE get_content_type(char* content);
static KIND get_kind(char* content);


TYPE compile_type(CODE *c, char* buffer)
{
    TOKEN* next = get_next_token(c->source);
    TYPE t;

    rollback(c->source);

    t = get_content_type(next->content);
    handle_type(t, c, next);

    if (buffer != NULL) strncpy(buffer, next->content, 300);

    release_token(&next);
    return t;

}

unsigned int compile_comma(CODE* c)
{
    TOKEN* t = NULL;
    char character;

    t = get_next_token(c->source);
    rollback(c->source);

    if (t == NULL) return 0;

    if (t->type != IMPLEMENTED_SYMBOL)
    {
        release_token(&t);
        return 0;
    }

    character = *(t->content);

    if (character == ',') {
        compile_symbol(c, ",");
    }
    release_token(&t);

    return (character == ',');

}

static unsigned int is_class_header(char* content)
{
    if (content[0] == '\0') return 0;

    return (strcmp(content, "static") == 0 ||
            strcmp(content, "field") == 0);
}



void compile_classheader(CODE* c)
{
    char content[400];


    get_next_token_content(c, content);
    while (is_class_header(content))
    {
        compile_classvardec(c);
        get_next_token_content(c, content);
    }
}

void compile_classbody(CODE* c)
{

    char content[400];

    get_next_token_content(c, content);

    if (*content == '\0') return;

    while (strcmp(content, "}") != 0)
    {
        compile_subroutinedec(c);
        get_next_token_content(c, content);
        if (*content == '\0') return;
    }

    return;
}

void compile_class(CODE* c)
{

    /**
    *       <class> ::= class <className> { <classvardec>* <subroutinedec>* }
    */
    TOKEN* next;
    TABLE* table = new_table("class");
    c->table = table;

    opentag(c, "class");
    compile_keyword(c, "class");
    compile_identifier(c);
    compile_symbol(c, "{");

    compile_classheader(c);
    compile_classbody(c);

    compile_symbol(c, "}");

    closetag(c, "class");

    release_table(&table);

}


void compile_vardec(CODE* c)
{
    TYPE t;
    char buffer[300];
    opentag(c, "varDec");

    compile_keyword(c, "var");

    t = compile_type(c, buffer);

    do {
        update_table(c, buffer, LOCAL, t);
        compile_identifier(c);
    } while (compile_comma(c));

    compile_symbol(c, ";");

    closetag(c, "varDec");
}

static void compile_subroutine_vardec(CODE* c)
{
    char content[300];

    get_next_token_content(c, content);
    while (strcmp(content, "var") == 0)
    {
        compile_vardec(c);
        get_next_token_content(c, content);
    }


}

void compile_subroutinebody(CODE* c)
{
    /*
    *     <subroutinebody> ::= {<vardec>* <statements> }
    */

    opentag(c, "subroutineBody");

    compile_symbol(c, "{");
    compile_subroutine_vardec(c);
    compile_statements(c);

    compile_symbol(c, "}");
    closetag(c, "subroutineBody");

    // Exits the local scope by freeing the topmost symbol table
    exit_scope(c);
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
        return ;
    }

    for (int i = 0; predecs[i] != NULL; i++)
    {
        if (strcmp(predecs[i], t->content) == 0)
        {
            compile_keyword(c, predecs[i]);
            init_scope(c, i);
            release_token(&t);
            return;
        }
    }


    return;
}


KIND compile_classfield(CODE* c)
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
            return get_kind(fieldtypes[i]);
        }
    }

    return -1;
}

void compile_classvardec(CODE* c)
{
    /**
    *      <classvardec> ::= (static | field) <type> <varname> (, <varname>)* ;
    */
    TYPE t;
    KIND k;
    char typename[300];

    opentag(c, "classVarDec");

    k = compile_classfield(c);
    t = compile_type(c, typename);

    do {
        update_table(c, typename, k, t);
        compile_identifier(c);

    } while (compile_comma(c));

    compile_symbol(c, ";");

    closetag(c, "classVarDec");

    return;
}

void compile_function_type(CODE* c)
{

    char content[300];

    get_next_token_content(c, content);

    if (strcmp(content, "void") == 0)
    {
        compile_keyword(c, "void");
        return;
    }

    compile_type(c, NULL);
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
    TYPE type;
    char typename[300];

    compile_symbol(c, "(");
    opentag(c, "parameterList");

    t = get_next_token(c->source);
    rollback(c->source);

    if (strcmp(t->content, ")") == 0)
    {
        goto end_of_compile_paremter_list_fn;
    }

    do {
        type = compile_type(c, typename);
        update_table(c, typename, ARGUMENT, type);
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

    return CLASSNAME;
}



static KIND get_kind(char* content)
{
    char* kinds[] = {
        "static", "field"
    };

    for (int i = 0; i < 2; i++)
    {
        if (strcmp(kinds[i], content) == 0) return i;
    }

    return -1;
}
