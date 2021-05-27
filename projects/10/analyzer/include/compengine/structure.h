/**
*       Headers for the program structure
*/

void compile_subroutinecall(CODE* c);

typedef enum {
    INT,
    CHAR,
    BOOLEAN,
    CLASSNAME,
    INVALID_TYPE
} TYPE;



void compile_type(CODE *c);
