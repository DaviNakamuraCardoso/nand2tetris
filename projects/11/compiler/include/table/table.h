/**
*
*       Header files for the table module
*
*/


#ifndef HASHSIZE
#define HASHSIZE 101
#endif

#ifndef __TYPE
#include <table/types.h>
#define __TYPE
#endif

#ifndef __KIND
#include <table/kinds.h>
#define __KIND
#endif


typedef struct _variable {
    char* name;
    KIND kind;
    TYPE type;
    unsigned int index;
    struct _variable* next;

} __VARIABLE;

typedef struct _table {
    __VARIABLE** variables;
    struct _table* next;
    int kind_counter[4];

} TABLE;

// Constructors
TABLE* new_table(void);
__VARIABLE* new_variable(char* name, KIND k, TYPE t);

// Deallocators
void release_table(TABLE** t);
static void release_variable(__VARIABLE* v);

static unsigned int hash(char* s);
void add_hash(TABLE* root, __VARIABLE* variable);
__VARIABLE* search_table(TABLE* root, char* name);


void add_var(TABLE* root, char* varname, KIND k, TYPE t);
