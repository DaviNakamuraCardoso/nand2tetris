/**
*
*       Functions writer for the Davi Compiler Collection
*
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <compengine/compile.h>
#include <table/parser.h>
#include <writer/writer.h>
#include <writer/assignments.h>
#include <writer/functions.h>


static void write_function_call(CODE* c, char* function_name, unsigned int nargs)
{
    char cmd[300];

    sprintf(cmd, "call %s %i", function_name, nargs);
    writevm(c, cmd);

    return;
}

static void write_push_pointer0(CODE* c)
{
    return;
}


// For method calls, is necessary to push the object as the first argument
unsigned int push_methodarg(CODE* c, char* classname)
{
    char identifier[300];
    unsigned int is_method;

    get_next_token_content(c, identifier);

    is_method = get_classname(c, identifier, classname);

    // Methods receive the object as first argument
    if (is_method)
    {
        write_push(c, identifier);
        return 1;
    }

    return 0;

}



void write_functioncall(CODE* c, char* classname, char* fname, unsigned int nargs)
{
    char function[700];

    sprintf(function, "%s.%s", classname, fname);

    write_function_call(c, function, nargs);

}


void write_privatecall(CODE* c, char* fname, unsigned int nargs)
{
    char classtype[300];


    get_classname(c, "this", classtype);

    write_functioncall(c, classtype, fname, ++nargs);
    return;
}
