

#ifndef __STDJACKLH
#define __STDJACKLH

#include "../vm.h"
#include "../tokenizer.h"
#include "memory.h"
#include "string.h"

typedef struct _stdf {
    char* name; 
    void (*f) (Program*, unsigned short);
} Std; 

int stdlib(Source* p);

#endif

