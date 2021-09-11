#include <stdio.h>
#include <stdlib.h>
#include <tokens.h>

static char* cmds[] = {
    [PUSH]      = "push",
    [POP]       = "pop",
    [LABEL]     = "label", 
    [GOTO]      = "goto",
    [IFGOTO]    = "if-goto",
    [CALL]      = "call",
    [FUNCTION]  = "function",
    [ADD]       = "add",
    [SUB]       = "sub",
    [MULT]      = "mult",
    [DIV]       = "div",
    [GT]        = "gt",
    [LT]        = "lt",
    [EQ]        = "eq"
};

static char* memsegs[] = {
    [CONSTANT]  = "constant", 
    [STATIC]    = "static",
    [ARGUMENT]  = "argument",
    [LOCAL]     = "local",
    [THIS]      = "this",
    [THAT]      = "that",
    [POINTER]   = "pointer",
    [TEMP]      = "temp"
};

Hash** cmdhash(void)
{
    Hash** h = new_hash();
    for (unsigned int i = 0; i < sizeof(cmds) / sizeof(char*); i++)
    {
       add_hash(h, cmds[i], i); 
    }

    return h;
} 

Hash** mseghash(void)
{
    Hash** h = new_hash();
    for (unsigned int i = 0; i < sizeof(memsegs) / sizeof(char*); i++)
    {
       add_hash(h, memsegs[i], i); 
    }

    return h;
}

