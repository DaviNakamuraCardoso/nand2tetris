/** Header for the tokenizer module **/

#define MAX_ASCII 177

typedef struct _symbol
{
    unsigned int exists:1;
    struct _symbol *next[MAX_ASCII];
} SYMBOL;

SYMBOL* new_symbol(void);

void release_symbol(SYMBOL** root);

void add_symbol(SYMBOL* root, char* key);

unsigned int search_symbol(SYMBOL* root, char* key);

unsigned int search_one_char(SYMBOL* root, char* key);

void add_symbols_from_file(SYMBOL* root, char* filename);
