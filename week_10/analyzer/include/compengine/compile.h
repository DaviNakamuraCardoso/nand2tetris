
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

/**
*       Handling implemented elements
*/
unsigned int compile_symbol(CODE* c, char* symbol);
unsigned int compile_keyword(CODE* c, char* keyword);

unsigned int compile_identifier(CODE* c);
unsigned int compile_stringconstant(CODE* c);
unsigned int compile_integerconstant(CODE* c);


/**
*       Assertions
*/
void assert_type(TOKEN_TYPE a, TOKEN_TYPE b, int* status);
void assert_content(char* a, char* b, int* status);


/**
*   Useful XML functions
*/
void opentag(CODE* c, const char* tagname);
void closetag(CODE* c, const char* tagname);

unsigned int compile_keylist(CODE* c, char* keylist[], void (*handler) (CODE*, char*));

short is_next(CODE* c, char* content, TOKEN_TYPE type); 
