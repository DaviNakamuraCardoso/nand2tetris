
#ifndef __HASHH
#define __HASHH

typedef struct _sh {
    short type;
    char* key;
    struct _sh* next; 
} sh; 


sh** new_hash(void); 
void add_hash(sh** h, char* key, short value); 
short gethash(sh** h, char* key); 

#endif 

