/**
*
*       Header for the table parser
*
*/


static char* get_vm_name(KIND kind);
void get_variable(CODE* c, char* varname, char* buffer); 
void update_table(CODE* c, char* classname, KIND k, TYPE t);



// Starts and finishes a scope
void init_scope(CODE* c, __F_TYPE type);
void exit_scope(CODE* c);
