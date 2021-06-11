/**
*
*       Writes all loops for the Davi Compiler Collection (DCC)
*       (c) 2021 Davi Nakamura Cardoso
*
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <compengine/compile.h>
#include <writer/writer.h>
#include <writer/loops.h>


void write_label(CODE* c, char* buffer)
{
    sprintf(buffer, "label LABEL_%li", get_counter(c));
    writevm(c, buffer);
    return;
}


static void write_flow(CODE* c, char* label, const char* instruction)
{
    char buffer[300];
    sprintf(buffer, "%s %s", instruction, label);
    writevm(c, buffer);
    return;
}

void write_ifgoto(CODE* c, char* label)
{
    write_flow(c, label, "if-goto");
    return;
}

void write_goto(CODE* c, char* label)
{
    write_flow(c, label, "goto");
    return;
}
