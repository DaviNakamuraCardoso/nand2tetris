/**
*
*
*
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <compengine/compile.h>
#include <writer/writer.h>


void writevm(CODE* c, char* line)
{
    if (c->vm == NULL) return;
    fprintf(c->vm, "%s\n", line);
    return;
}
