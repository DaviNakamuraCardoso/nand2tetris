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
void add_keywords_and_symbols(SYMBOL* root, char* filename, char** (*handler) (char*, char*))
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
        add_symbol(root, buff, handler);
    }
    free(content);

    return;

}


char** get_string_literal(char* expression, char* b)
{
    int i;
    char *first, *last, *buff, **ret;

    // Get the first quote
    first = strchr(expression, '"');

    // If there are no double quotes, return NULL
    if (first == NULL) {
        buff = NULL;
        last = expression;
        goto endbuff;
    }

    // Get the double quote after the first (does not support escape)
    last = strchr(first+1, '"');

    if (last == NULL)
    {
        printf("Error: unmatched quote in string declaration\n");
        exit(1);
    }

    buff = malloc((3+last-first) * sizeof(char));

    for (i = 0; first[i+1] != '"'; i++)
    {
        buff[i] = first[i+1];
    }

    buff[i] = '\0';
    goto endbuff;

    endbuff:
    {
        ret = malloc(3*sizeof(char*));

        ret[0] = last+1;
        ret[1] = "StringConstant";
        ret[2] = buff;
    }

    return (ret);
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


char** handle_symbol_or_keyword(char* text, char* buff, char* key)
{
    char **ret;

    ret = malloc(3*sizeof(char*));

    ret[0] = text+strlen(buff);
    ret[1] = strdup(key);
    ret[2] = buff;

    return (ret);
}

char** symbol_handler(char* text, char* buff)
{
    return (handle_symbol_or_keyword(text, buff, "symbol"));
}

char** keyword_handler(char* text, char* buff)
{
    return (handle_symbol_or_keyword(text, buff, "keyword"));
}


SYMBOL* symbol_manager(char* base_dir)
{
    SYMBOL* s;

    char path_keywords[200], path_symbols[200];

    sprintf(path_symbols, "%s/symbols.csv", base_dir);
    sprintf(path_keywords, "%s/keywords.csv", base_dir);

    s = create_symbol();

    add_keywords_and_symbols(s, path_symbols, symbol_handler);
    add_keywords_and_symbols(s, path_keywords, keyword_handler);
    add_symbol(s, "\"", get_string_literal);

    return s;
}
