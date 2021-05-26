
typedef struct _code {
    int* identation;
    FILE* source;
    FILE* target;
} CODE;

// Print the tag to a file using the current identation
void compilef(int identation, char* text, FILE* target);

// Increase the current identation by 1
void inc(int* identation);

// Decrease the current identation by 1
void dec(int* identation);

// Compiles a symbol
unsigned int compile_symbol(CODE* c, char* symbol);

unsigned int compile_keyword(CODE* c, char* keyword);

void assert_type(TOKEN_TYPE a, TOKEN_TYPE b, int* status);

void assert_content(char* a, char* b, int* status); 
