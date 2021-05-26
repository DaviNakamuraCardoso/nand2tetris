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
    open_expression(c);
    close_expression(c);
    return;
}


void open_expression(CODE* c)
{
   compilef(*(c->identation), "<expression>", c->target);
   inc(c->identation);
   return;
}

void close_expression(CODE* c)
{
    dec(c->identation);
    compilef(*(c->identation), "</expression>", c->target);
    return;
}
