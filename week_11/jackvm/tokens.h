#include "hash.h"

#ifndef __TOKENSH
#define __TOKENSH

enum command { 
    PUSH, 
    POP,
    LABEL,
    GOTO,
    IFGOTO,
    CALL,
    FUNCTION,
    ADD,
    SUB,
    MULT,
    DIV,
    GT,
    LT,
    EQ
}; 

enum memseg {
    CONSTANT, 
    STATIC,
    ARGUMENT,
    LOCAL, 
    THIS,
    THAT,
    POINTER,
    TEMP
};
    
sh** cmdhash(void);
sh** mseghash(void);

#endif 
