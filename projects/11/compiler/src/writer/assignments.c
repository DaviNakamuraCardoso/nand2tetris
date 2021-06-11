/**
*
*
*       Generates VM code for assigments
*
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <compengine/compile.h>
#include <table/parser.h>
#include <writer/assignments.h>


static void write_stack_cmd(CODE* c, char* varname, const char* cmd)
{
    char variable[200], vm[300];

    get_variable(c, varname, variable);
    sprintf(vm, "%s %s", cmd, variable);
    writevm(c, vm);
    return;
}

void write_pop(CODE* c, char* varname)
{
    write_stack_cmd(c, varname, "pop");
    return;
}

void write_push(CODE* c, char* varname)
{
    write_stack_cmd(c, varname, "push");
    return;
}
