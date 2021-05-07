/**
*       Performs the precompilation, skipping whitespaces and comments
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tokenizer/precomp.h>


unsigned int is_whitespace(char* ptr)
{
    switch (*ptr) {
        case 0:
            return 0; 
        case ' ':
        case '\t':
        {
            return 1;
        }
    }
    return 0;
}

unsigned int is_not_endofline(char* c)
{
    return (*(c) != '\n');
}

unsigned int is_not_endof_comment(char* c)
{
    return !(*(c) == '*' && (*c+1) == '/');
}

char* cycle_text(char* text, unsigned int (*validator) (char*))
{
    char* ptr;

    for (ptr = text; validator(ptr) && (*ptr) != '\0'; ptr++) {}

    return ptr;
}


char* handle_whitespaces(char* text)
{
    return cycle_text(text, is_whitespace);
}

char* handle_inline_comments(char* text)
{
    // Returns the char after the end of line character
    return (cycle_text(text, is_not_endofline)+1);
}

char* handle_multiple_line_comments(char* text)
{
    return (cycle_text(text, is_not_endof_comment)+1);
}
