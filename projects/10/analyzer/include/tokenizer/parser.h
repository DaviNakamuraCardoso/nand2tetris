

void write_xml(char** result, FILE* xml);

TOKEN_TYPE get_type(SYMBOL* tables_type, char* token);

SYMBOL* new_types_table(void);

char* get_tag(TOKEN_TYPE type); 
