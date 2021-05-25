/*
*       Compile statements for the Davi Compiler Collection (DCC)
*       (c) 2021 Davi Nakamura Cardoso
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <tokenizer/tokens.h>
#include <compengine/parser.h>
#include <compengine/compile.h>
#include <compengine/expressions.h>
#include <compengine/statements.h>

// Private functions
void open_statement(int* identation, char* keyword, FILE* target);
void close_statement(int* identation, char* keyword, FILE* target);

void compile_statements(CODE* c)
{
    return;
}

void compile_while(CODE* c)
{
    int i;
    /***
        <whileStatement> ::= while ( <expression> ) { <statements> }
    */
    open_statement(c->identation, "while", c->target);  // '<whileStatement>'

    compile_keyword(c, "while");

    compile_symbol(c, "(");        // (

    compile_expression(c);          // <expression>

    compile_symbol(c, ")");       // )

    compile_symbol(c, "{");

    compile_statements(c);          // <statements>

    compile_symbol(c, "}");

    close_statement(c->identation, "while", c->target); // '</whileStatement>'

    return;
}


void open_statement(int* identation, char* keyword, FILE* target)
{
    char tag[500];
    sprintf(tag, "<%sStatement>", keyword);

    compilef(*identation, tag, target);

    inc(identation);

    return;
}

void close_statement(int* identation, char* keyword, FILE* target)
{
    char tag[500];
    sprintf(tag, "</%sStatement>", keyword);
    dec(identation);
    compilef(*identation, tag, target);

    return;

}
