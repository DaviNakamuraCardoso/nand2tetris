// Basic error function
void error(char* message);

// Translates basic commands (arithmetic and memory instructions)
void base_translation(FILE* f, FILE* d);

// Checks if a given name is a directory or not
unsigned int is_dir(const char* name);

// Checks if a file is a Virtual Machine file
unsigned int is_vm(const char* filename);
