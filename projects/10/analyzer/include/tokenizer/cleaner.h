
void add_keywords_and_symbols(SYMBOL* root, char* filename, char** (*handler) (char*, char*));

char* get_string_literal(char* expression);

char* get_number_constant(char* expression);

SYMBOL* symbol_manager(void);
