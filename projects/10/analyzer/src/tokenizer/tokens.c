/**
*       "token" module for the Davi Compiler Collection (DCC)
*       (c) 2021 by Davi Nakamura Cardoso
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <tokenizer/tokens.h>

// Generates a new symbol and set existence to false
SYMBOL* create_symbol(void)
{
    int i;
    SYMBOL* s;

    s = malloc(sizeof(SYMBOL));
    s->exists = 0;

    for (i = 0; i < SYMBOL_NUM; i++)
    {
        s->next[i] = NULL;
    }

    return s;

}

void release_symbol(SYMBOL** root)
{
    int i;

    // Check null
    if (*root == NULL) return;

    // Free all the children nodes
    for (i = 0; i < SYMBOL_NUM; i++)
    {
        release_symbol(&(*root)->next[i]);
    }

    // After releasing all the children nodes, free the parent and set the pointer
    // to NULL
    free(*root);
    *root = NULL;

    return;

}

SYMBOL* set_symbol(SYMBOL* root, char* key)
{
    int i, a;
    SYMBOL* current;

    current = root;
    // Adds a symbol to each character in the string
    for (i = 0; key[i] != '\0'; i++)
    {
        a = (int) key[i];

        // If a next node with the letter does not exist, create one
        if (current->next[a] == NULL)
        {
            current->next[a] = create_symbol();
        }

        current = current->next[a];
    }

    return current;
}

// Adds a symbol to a root
void add_symbol(SYMBOL* root, char* key, ...)
{
    va_list ap;
    SYMBOL* s;
    char** (*handler) (char*, char*);

    va_start(ap, key);

    handler = va_arg(ap, char** (*) (char*, char*));

    // Set the space of a symbol
    s = set_symbol(root, key);

    // Set the exists in the last symbol to true
    s->exists = 1;
    s->handler = handler;

    return;
}

SYMBOL* get_symbol(SYMBOL* root, char* s)
{

    int i, a;
    SYMBOL* current;

    current = root;

    // Adds a symbol to each character in the string
    for (i = 0; s[i] != '\0'; i++)
    {
        a = (int) s[i];

        // If a next node with the letter does not exist, create one
        if (current == NULL)
        {
            return NULL;
        }
        current = current->next[a];
    }

    return current;

}

unsigned int search_symbol(SYMBOL* root, char* symbol)
{
    SYMBOL* s;

    s = get_symbol(root, symbol);

    if (s == NULL)
    {
        return 0;
    }

    return (s->exists);
}

SYMBOL* get_first_symbol(SYMBOL* root, char* key)
{
    int i, size;
    SYMBOL* current;

    size = strlen(key);

    char buff[size];

    strcpy(buff, key);

    for (i = 1; i < size; i++)
    {
        // Substring
        buff[i] = '\0';

        current = get_symbol(root, buff);
        if (current != NULL) return current;

        // Restore previous state
        buff[i] = key[i];

    }

    return NULL;
}

char** handle_symbol(SYMBOL* root, char* symbol, char* text, char* buff)
{
    SYMBOL* s;

    s = get_first_symbol(root, symbol);

    if (s != NULL)
    {
        if (s->handler != NULL)
        {
            return s->handler(text, buff);
        }
    }

    return NULL;

}
