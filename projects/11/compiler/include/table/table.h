/**
*
*       Header files for the table module
*
*/

typedef enum {
    INTEGER,
    CHARACTER,
    BOOLEAN,
    CLASS_TYPE
} TYPE;

typedef enum {
    STATIC,
    FIELD,
    ARGUMENT,
    LOCAL
} KIND;

typedef struct _table {
    char* name;
    char* type_name;
    TYPE type;
    KIND kind;
    short index;
    struct _table* next;
} TABLE;


TABLE* new_table(char* name, char* type_name, TYPE type, KIND kind, short index);
void release_table(TABLE** table); 
