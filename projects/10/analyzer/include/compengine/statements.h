
typedef enum {
    INVALID_STATEMENT,
    LET,
    IF,
    WHILE,
    DO,
    RETURN
} STATEMENT;

void compile_while(CODE* c);

void compile_statements(CODE* c);
