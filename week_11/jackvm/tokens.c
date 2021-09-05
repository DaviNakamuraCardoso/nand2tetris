#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"

static unsigned int match(char* cmd, unsigned short index); 
static unsigned int matchm(char* memseg, unsigned short index); 
static Token* new_token(enum cmd c, enum memseg m, long value); 

const char* cmds[] = {
    "pop",
    "push",
    "label", 
    "goto",
    "if-goto",
    "call",
    "function",
    "add",
    "sub",
    "mult",
    "div",
    "gt",
    "lt",
    "eq"
};

static const char* memsegs[] = {
    "static",
    "argument",
    "local",
    "this",
    "that",
    "pointer",
    "temp"
};

     
enum command cmdtype(char* cmd)
{
    
    for (int i = 0; i < sizeof(cmds) / sizeof(char*); i++)
    {
        if (match(cmd, i)) return i; 
    }

    return -1; 
}


enum memseg memsegtype(char* memseg)
{
    for (int i = 0; i < sizeof(cmds) / sizeof(char*); i++)
        if (matchm(cmd, i)) return i;

    return -1; 

}

static Token* new_token(enum cmd c, enum memseg m, long value)
{
    Token* t = malloc(sizeof(Token)); 
    t->cmd = c; 
    t->memseg = m;
    t->value = value; 

    return t; 

}


static unsigned int match(char* cmd, unsigned short index)
{

    for (int i = 0; cmd[i] != '\0' && cmds[index][i] != '\0'; i++)
        if (cmd[i] != cmds[index][i]) return 0; 
    
    return cmds[index][i] == cmd[i]; 
}

static unsigned int matchm(char* memseg, unsigned short index)
{
    for (int i = 0; memseg[i] != '\0' && memsegs[index][i] != '\0'; i++)
        if (memseg[i] != memsegs[index][i]) return 0; 

    return memsegs[index][i] == memseg[i]; 
}
