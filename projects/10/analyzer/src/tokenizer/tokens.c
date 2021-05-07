/**
*       "token" module for the Davi Compiler Collection (DCC)
*       (c) 2021 by Davi Nakamura Cardoso
*/

#include <stdio.h>
#include <stdlib.h>
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

// Adds a symbol to a root
void add_symbol(SYMBOL* root, char* symbol)
{
    int i, a;
    SYMBOL* current;

    current = root;

    // Adds a symbol to each character in the string
    for (i = 0; symbol[i] != '\0'; i++)
    {
        a = (int) symbol[i];

        // If a next node with the letter does not exist, create one
        if (current->next[a] == NULL)
        {
            current->next[a] = create_symbol();
        }

        current = current->next[a];
    }

    // Set the exists in the last symbol to true
    current->exists = 1;

    return;

}

unsigned int search_symbol(SYMBOL* root, char* symbol)
{
    int i, a;
    SYMBOL* current;

    current = root;

    // Adds a symbol to each character in the string
    for (i = 0; symbol[i] != '\0'; i++)
    {
        a = (int) symbol[i];

        // If a next node with the letter does not exist, create one
        if (current == NULL)
        {
            return 0;
        }
        current = current->next[a];
    }

    if (current == NULL) return 0;

    return (current->exists);

}
