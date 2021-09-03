// Get the filename based on the source name
char* filename(char* str, int len);

// Adds all symbols in the source file
void parse(TABLE* root, FILE* f, FILE* dest);
