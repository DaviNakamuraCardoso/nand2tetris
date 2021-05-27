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
#include <compengine/structure.h>

// Private functions
void open_statement(int* identation, char* keyword, FILE* target);
void close_statement(int* identation, char* keyword, FILE* target);

void open_statements(CODE* c);
unsigned int handle_statements(CODE* c, STATEMENT type);
void close_statements(CODE* c);
STATEMENT get_statement(TOKEN* t);

void compile_statements(CODE* c)
{
    /*
    *   <statements>    ::= <statement>*
    *   <statement>     ::= <let> | <if> | <while> | <do> | <return>
    */

    TOKEN* next;
    STATEMENT type;

    open_statements(c);
    do {
        next = get_next_token(c->source);

        if (next == NULL) break;
        type = get_statement(next);
        rollback(c->source);
        release_token(&next);

    } while (handle_statements(c, type));
    close_statements(c);

    return;

}

void compile_else(CODE* c)
{
    int status;
    TOKEN* next;

    /*
    *   <else> ::= else { <statements> }
    */

    next = get_next_token(c->source);

    if (next == NULL) return;

    rollback(c->source);

    assert_type(next->type, KEYWORD, &status);
    assert_content(next->content, "else", &status);

    release_token(&next);

    if (!status) return;

    compile_keyword(c, "else");

    compile_symbol(c, "{");

    compile_statements(c);

    compile_symbol(c, "}");


    return;
}

void compile_if(CODE* c)
{
    open_statement(c->identation, "if", c->target);

    compile_keyword(c, "if");

    compile_symbol(c, "(");

    compile_expression(c);

    compile_symbol(c, ")");

    compile_symbol(c, "{");

    compile_statements(c);

    compile_symbol(c, "}");

    compile_else(c);

    close_statement(c->identation, "if", c->target);

    return;
}

void compile_while(CODE* c)
{
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

void compile_return(CODE* c)
{
    /**
    *   <return> ::= return <expression>? ;
    */

    TOKEN* next;

    open_statement(c->identation, "return", c->target);
    compile_keyword(c, "return");

    next = get_next_token(c->source);
    rollback(c->source);

    if (strcmp(next->content, ";") != 0)
    {
        compile_expression(c);
    }

    compile_symbol(c, ";");
    close_statement(c->identation, "return", c->target);

    release_token(&next);
    return;

}

void compile_let(CODE* c)
{
    /**
    *       <let> ::= let <identifier> = <expressions> ;
    */
    open_statement(c->identation, "let", c->target);
    compile_keyword(c, "let");

    // Check for an identifier
    compile_identifier(c);

    compile_symbol(c, "=");

    compile_expression(c);

    compile_symbol(c, ";");

    close_statement(c->identation, "let", c->target);

    return;
}

void compile_do(CODE* c)
{

    /**
    *       <do> ::= do <subroutinecall> ;
    */
    open_statement(c->identation, "do", c->target);

    compile_keyword(c, "do");

    compile_subroutinecall(c);

    compile_symbol(c, ";");

    close_statement(c->identation, "do", c->target);

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

void open_statements(CODE* c)
{
    compilef(*(c->identation), "<statements>", c->target);
    inc(c->identation);
    return;
}

void pass(CODE* c) {return;}

unsigned int handle_statements(CODE* c, STATEMENT type)
{
    if (type == INVALID_STATEMENT) return 0;

    void (*handlers[]) (CODE*) = {
        pass,
        compile_let,
        compile_if,
        compile_while,
        compile_do,
        compile_return
    };

    handlers[type](c);

    return 1;
}

void close_statements(CODE* c)
{
    dec(c->identation);
    compilef(*(c->identation), "</statements>", c->target);
    return;
}

STATEMENT get_statement(TOKEN* t)
{
    if (t->type != KEYWORD) return INVALID_STATEMENT;

    switch (t->content[0]) {
        case 'w': return WHILE;
        case 'i': return IF;
        case 'd': return DO;
        case 'l': return LET;
        case 'r': return RETURN;
    }

    return INVALID_STATEMENT;
}
