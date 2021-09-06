#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

#define HASHSIZE 30

sh** new_hash(void)
{
    sh **h = calloc(sizeof(sh*), HASHSIZE);
    for (int i = 0; i < HASHSIZE; i++)
    {
        h[i] = NULL; 
    }

    return h;
}

sh* new_sh(char* key, short type)
{
    sh* hn = malloc(sizeof(sh));
    hn->key = strdup(key);
    hn->type = type; 

    return hn; 
} 

unsigned int hash(char* key)
{
    unsigned int val = 0; 
    for (char *c = key; *c != '\0'; c++)
        val += (*c) * 31; 

    return val % HASHSIZE; 
}

void add_hash(sh** h, char* key, short value)
{
    sh *hn, *new = new_sh(key, value);
    int index = hash(key);
    if (h[index] == NULL)
    {
        h[index] = new;
        return;
    }

    hn = h[index];
    h[index] = new; 
    new->next = hn;
    return;
}

unsigned int strmatch(char* s1, char* s2)
{
    int i;
    for (i = 0; s1[i] != '\0' && s2[i] != '\0'; i++)
        if (s1[i] != s2[i]) return 0;

    return s1[i] == s2[i];
}

short gethash(sh** h, char* key)
{
    unsigned int index = hash(key);
    for (sh* np = h[index]; np != NULL; np = np ->next)
    {
        if (strmatch(np->key, key)) return np->type;
    }

    return -1;
}

    
