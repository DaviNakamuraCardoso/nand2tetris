typedef struct _table {
    char* value;
    struct _table* next[200];
    unsigned int locked:1;
} TABLE;

// Table initialization
TABLE* init_table(TABLE* root, char c);

// Adding commands (labels, vars, macros) to the table
void add_command(TABLE* root, char* cmd, char* value);

// Adds all commands from a CSV file
void add_values(TABLE* root, FILE* f);

// Adds all labels
void setup_labels(TABLE* root, FILE* f); 

// Adds all variables and labels
void setup_vars(TABLE* root, FILE* f);

// Search instructions on table
char* search_ins(TABLE* root, char* cmd);
