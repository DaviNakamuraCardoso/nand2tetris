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


void compile_expression(CODE* c)
{
    /**
    *   <expression> ::= <term> (<op> <term>)*
    */
    opentag(c, "expression");
    // compile_term(c);

    /*
    while (compile_op(c))
    {
        compile_term(c);
    }
    */

    closetag(c, "expression");
    return;
}

unsigned int compile_expressionlist(CODE* c)
{
    /**
    *       <expressionlist> ::= (<expression> (, <expression>)*)?
    */


    return 1;
}

unsigned int compile_term(CODE* c)
{
    opentag(c, "term");

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

    char* list[] = {"+", "-", "*", "/", "&amp;", "|", "&lt;", "&gt;", "="};
    return compile_keylist(c, list, compile_symbol);
}
