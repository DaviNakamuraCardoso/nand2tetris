/*
*   Trees for the Davi Compiler Collection (DCC)
**/

#include <stdio.h>
#include <stdlib.h>
#include <tree.h>


// Ascii
int ascii(char c)
{
    int a;
    a = (int) c;

    // Lowercase
    if (a > 97) return (a-97+26);

    // Uppercase
    return (a-65);
}

// Initiate a tree
TREE* init_tree(void)
{
    TREE* t;
    int i;

    t = malloc(sizeof(TREE));

    for (i = 0; i < TREE_SIZE; i++)
    {
        t->next[i] = NULL;
    }

    t->push = NULL;
    t->pop = NULL;

    return t;
}


// Add a command
void add_command(TREE* root, char* memset,
    char* (*push) (char*, int), char* (*pop) (char*, int))
{
    int i, a;
    TREE* current;

    current = root;
    for (i = 0; memset[i] != '\0'; i++)
    {
        a = ascii(memset[i]);
        if (current->next[a] == NULL)
        {
            current->next[a] = init_tree();
        }

        current = current->next[a];
    }

    current->push = push;
    current->pop = pop;

    return;

}


char* search_command(TREE* root, char* mem, int val, COMMAND cmd)
{
    int i;
    TREE* current;
    char* ret;

    current = root;
    for (i = 0;  mem[i] != '\0'; i++)
    {
        if (current == NULL) return NULL;

        current = current->next[ascii(mem[i])];
    }

    if (current == NULL) return NULL;

    switch (cmd)
    {
        case POP:
        {
            if (current->pop == NULL) return NULL;
            return current->pop(mem, val);
        }
        case PUSH:
        {
            if (current->push == NULL) return NULL;
            fprintf(stderr, "About to return push function\n"); 
            return current->push(mem, val);
        }
    }

    return NULL;

}
