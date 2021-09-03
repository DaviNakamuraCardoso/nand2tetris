/**
*
*       Headers for the source structure
*
*
*/

typedef struct _tracker {
    unsigned long counter;
} TRACKER;

TRACKER* new_tracker(void);
void release_tracker(TRACKER* t); 
