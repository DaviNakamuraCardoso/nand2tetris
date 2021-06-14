/**
*
*       Header for the function writer
*
*
*/

void write_call(CODE* c, char* nargs);
unsigned int push_methodarg(CODE* c, char* classname);
void write_privatecall(CODE* c, char* fname, unsigned int nargs);
void write_functioncall(CODE* c, char* identifier, char* fname, unsigned int nargs); 
