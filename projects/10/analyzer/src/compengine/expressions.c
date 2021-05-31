/*
*
*       Set of functions for compiling various expressions
*       (c) 2021 Davi Nakamura Cardoso
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <tokenizer/tokens.h>
#include <compengine/parser.h>
#include <compengine/compile.h>
#include <compengine/expressions.h>


/*
*   Private functions
*/
void open_expression(CODE* c);
void close_expression(CODE* c);
unsigned int compile_termlist(CODE* c);


void compile_expression(CODE* c)
{
    /**
    *   <expression> ::= <term> (<op> <term>)*
    */
    opentag(c, "expression");

    do {
        compile_term(c);
    } while (compile_op(c));

    closetag(c, "expression");
    return;
}

static short is_next(CODE* c, char* content, TOKEN_TYPE type)
{
    unsigned int status = 1;
    TOKEN* next = NULL;

    next = get_next_token(c->source);
    rollback(c->source);


    if (next == NULL)
    {
        return -1;
    }

    assert_type(type, next->type, &status);
    assert_content(content, next->content, &status);

    release_token(&next);

    return status;

}

unsigned int compile_inbraces(CODE* c)
{
    if (is_next(c, "(", IMPLEMENTED_SYMBOL) != 1) return 0;

    compile_symbol(c, "(");

    compile_expression(c);

    compile_symbol(c, ")");

    return 1;
}

unsigned int compile_expressionlist(CODE* c)
{
    /**
    *       <expressionlist> ::= (<expression> (, <expression>)*)?
    */

    opentag(c, "expressionList");

    if (is_next(c, ")", IMPLEMENTED_SYMBOL) == 0)
    {
        do {
            compile_expression(c);
        } while (compile_comma(c));

    }

    closetag(c, "expressionList");

    return 1;
}


unsigned int compile_term(CODE* c)
{
    opentag(c, "term");
    compile_termlist(c);
    closetag(c, "term");
}


unsigned int compile_keywordconstant(CODE* c)
{
    char* list[] = { "true", "false", "this", "null", NULL };

    return compile_keylist(c, list, compile_keyword);
}


unsigned int compile_unaryop(CODE* c)
{
    char* list[] = {"~", "-", NULL};
    return compile_keylist(c, list, compile_symbol);
}

unsigned int compile_op(CODE* c)
{

    char* list[] = {"+", "-", "*", "/", "&amp;", "|", "&lt;", "&gt;", "=", NULL};
    return compile_keylist(c, list, compile_symbol);
}

unsigned int compile_subroutinecall(CODE* c)
{
    short is_class, is_function = 0;
    TOKEN* t = NULL;

    t = get_next_token(c->source);

    is_class = is_next(c, ".", IMPLEMENTED_SYMBOL);
    is_function = is_next(c, "(", IMPLEMENTED_SYMBOL);

    if (is_class != 1 && is_function != 1)
    {
        if (t != NULL) release_token(&t);
        return 0;
    }
    rollback(c->source);


    opentag(c, "subroutineCall");

    compile_identifier(c);

    if (is_class)
    {
        compile_symbol(c, ".");
        compile_identifier(c);
    }

    compile_symbol(c, "(");

    compile_expressionlist(c);

    compile_symbol(c, ")");

    closetag(c, "subroutineCall");

    return 1;
}
unsigned int compile_termlist(CODE* c)
{
    unsigned int i;
    unsigned int (*functions[]) (CODE*) = {
        compile_identifier,
        compile_integerconstant,
        compile_keywordconstant,
        compile_stringconstant,
        compile_inbraces
    };

    for (i = 0; i < 5; i++)
    {
        if (functions[i](c)) return 1;
    }

    return 0;
}
