/*
*       Cleaner module for the Davi Compiler Collection
*       Input: sourcefile.jack
*       Output: tokens.xml
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tokenizer/tokens.h>
#include <tokenizer/precomp.h>
#include <tokenizer/reader.h>
#include <tokenizer/cleaner.h>

// Adds all keywords and symbols described in a file
void add_keywords_and_symbols(SYMBOL* root, char* filename)
{
    int i, j;
    char* content, buff[200];

    content = get_file(filename);

    for (i = 0; content[i] != '\0'; i++)
    {
        for (j = 0; content[i] != '\n'; j++, i++)
        {
            buff[j] = content[i];
        }
        buff[j] = '\0';
        add_symbol(root, buff);
    }
    free(content);

    return;

}

char* keyword_handler(char* expression)
{

}

char* get_string_literal(char* expression)
{
    int i;
    char *first, *last, *buff;

    // Get the first quote
    first = strchr(expression, '"');

    // If there are no double quotes, return NULL
    if (first == NULL) return NULL;

    // Get the double quote after the first (does not support escape)
    last = strchr(first+1, '"');

    if (last == NULL)
    {
        printf("Error: unmatched quote in string declaration\n");
        return NULL;
    }

    buff = malloc((3+last-first) * sizeof(char));

    for (i = 0; first[i+1] != '"'; i++)
    {
        buff[i] = first[i+1];
    }

    buff[i] = '\0';

    return buff;
}

unsigned int is_number(char c)
{
    return (c >= '0' && c <= '9');
}

char* get_number_constant(char* expression)
{
    int i, j, k;
    char *ret;

    // Get the first number occurrence
    for (i = 0; !is_number(expression[i]) && expression[i] != '\0'; i++) {}

    // Get the last number occurrence
    for (j = i; is_number(expression[j]); j++) { }

    // Returns null if there are no numbers
    if ((j-i) == 0) return NULL;

    ret = malloc((1+j-i) * sizeof(char));

    for (k = 0; k < (j-i); k++)
    {
        ret[k] = expression[k+i];
    }

    ret[k] = '\0';

    return (ret);
}
