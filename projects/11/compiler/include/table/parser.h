/**
*
*       Header for the table parser
*
*/

typedef enum {
    CLASS_DECLARATION,

    // Subroutines
    METHOD,
    FUNCTION,
    CONSTRUCTOR,

    // Globals
    STATIC_DECLARATION,
    FIELD_DECLARATION,

    // Method components
    PARAMETER_LIST,
    LOCAL_DECLARATION,
    STATEMENTS,

    // Statements
    WHILE_STATEMENT,
    DO_STATEMENT,
    IF_STATEMENT,
    LET_STATEMENT,
    RETURN_STATEMENT,

    // Expressions
    TERM,
    SUBROUTINE_CALL

} BLOCK_TYPE;

typedef struct _xml {
    char* leave;
    struct _xml** branches;
} XML;


XML* new_xml(void);
