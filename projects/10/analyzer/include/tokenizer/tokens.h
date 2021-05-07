/**
*       Tokenizer header for the Davi Compiler Collection (DCC)
*/

// Max size of the ascii table
#define SYMBOL_NUM 127

// Trie that holds symbols
typedef struct _symbol
{
    unsigned int exists:1;
    struct _symbol* next[SYMBOL_NUM];
    char* (*handler) (char*);

} SYMBOL;


// Creates a new symbol
SYMBOL* create_symbol(void);

// Adds a symbol to a root
void add_symbol(SYMBOL* root, char* key, ...);

// Releases a Trie
void release_symbol(SYMBOL** root);

// Search a symbol in root
unsigned int search_symbol(SYMBOL* root, char* symbol);
