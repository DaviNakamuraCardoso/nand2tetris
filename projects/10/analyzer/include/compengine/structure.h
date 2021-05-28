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

void compile_vardec(CODE* c);

void compile_subroutinebody(CODE* c);

void compile_parameterlist(CODE* c);

void compile_subroutinedec(CODE* c);

void compile_classvardec(CODE* c);

void compile_class(CODE* c);

unsigned int compile_comma(CODE* c); 
