
#ifndef __HASHH
#define __HASHH

typedef struct _hash {
    short type;
    char* key;
    struct _hash* next; 
} Hash; 


Hash** new_hash(void); 
void add_hash(Hash** h, char* key, short value); 
short gethash(Hash** h, char* key); 
void release_hash(Hash** root); 

#endif 

