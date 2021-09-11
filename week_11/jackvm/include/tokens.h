#include "hash.h"

#ifndef __TOKENSH
#define __TOKENSH

enum command { 
    PUSH    =   0, 
    POP     =   1,
    LABEL   =   2,
    GOTO    =   3,
    IFGOTO  =   4,
    CALL    =   5,
    FUNCTION=   6,
    ADD     =   7,
    SUB     =   8,
    MULT    =   9,
    DIV     =   10,
    GT      =   11,
    LT      =   12,
    EQ      =   13
}; 

enum memseg {
    CONSTANT        =   0, 
    STATIC          =   1,
    ARGUMENT        =   2,
    LOCAL           =   3, 
    THIS            =   4,
    THAT            =   5,
    POINTER         =   6,
    TEMP            =   7
};
    
Hash** cmdhash(void);
Hash** mseghash(void);

#endif 
