// Enums the different types of commands
typedef enum commands {PUSH, POP} COMMAND;

// Maximum number of tree connections
#define TREE_SIZE 52

// Stores the command handlers
typedef struct _tree {
    char* (*push) (char*, int);
    char* (*pop) (char*, int);
    struct _tree* next[TREE_SIZE];
} TREE;

// Create a tree
TREE* init_tree(void);

// Add a command
void add_command(TREE* root, char* memset,
    char* (*push) (char*, int), char* (*pop) (char*, int));

// Search command
char* search_command(TREE* root, char* mem, int val,  COMMAND cmd);
