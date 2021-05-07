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
    return !(*(c-1) == '*' && (*c) == '/');
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
    char* ret;

    // Gets a pointer to the first endofline
    ret = cycle_text(text, is_not_endofline);

    // Avoids empty strings
    ret = (*ret == '\0')? ret : (ret+1);

    return (ret);
}

char* handle_multiple_line_comments(char* text)
{
    char* ret;

    ret = cycle_text(text, is_not_endof_comment);

    ret = (*ret == '\0')? ret : (ret+1);

    return (ret);
}
