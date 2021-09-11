unsigned int isnullchar(char c);
unsigned int iscmd(char c); 
unsigned int isvalidsym(char c, char* syms, int i);
unsigned int isnumeral(char* str); 
unsigned int islabel(char* str); 
unsigned int issym(char c); 
unsigned int iscommentstart(char* buff);
void skipc(FILE* stream, char* buff); 


