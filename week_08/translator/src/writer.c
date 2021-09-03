/*
    Writer module for the Davi Compiler Collection (DCC)
*/
#include <stdio.h>
#include <stdlib.h>
#include <functioncmds.h>

// Writes a line of Hack Assembly language to the destination
void write_line(char* cmd, FILE* f)
{
    // Put your code here
    fprintf(f, "%s\n", cmd);
    return;
}

// Writes the basic definitions
void dir_defs(FILE* f)
{
    fprintf(f, "\n@256\nD=A\n@SP\nM=D\n@300\nD=A\n@LCL\nM=D\n@400\nD=A\n@ARG\nM=D\n@3000\nD=A\n@THIS\nM=D\n@3010\nD=A\n@THAT\nM=D\n");
    return;
}


// Writes the bootcode for a file
void bootcode(FILE* f)
{
    char* initial_call;
    initial_call = function_manager("call", "Sys.init", "0");
    fprintf(f, "%s\n", initial_call);
    return;

}
