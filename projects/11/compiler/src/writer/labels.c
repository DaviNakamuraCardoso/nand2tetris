/**
*
*       Determines counters for labels
*       (c) 2021 Davi Nakamura Cardoso
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <writer/labels.h>

static LABELS* lalloc(void)
{
    return (LABELS*) malloc(sizeof(LABELS));
}

LABELS* new_labels(void)
{
    LABELS* l = lalloc();
    l->counter = 0;

    return l;

}

void increase_counter(LABELS* l)
{
    l->counter = l->counter + 1;
    return;
}
