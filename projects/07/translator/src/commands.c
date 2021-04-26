/*
*
* Commands for the Davi Compiler Collection (DCC)
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tree.h>
#include <commands.h>


char* get_symbol(char* memset)
{
    char* symbol;

    symbol = malloc(6 * sizeof(char));

    switch (memset[0])
    {
        case 'a':
        {
            symbol = "ARG";
            break;
        }
        case 'l':
        {
            symbol = "LCL";
            break;
        }
        case 't':
        {
            switch (memset[2])
            {
                case 'i':
                {
                    symbol = "THIS";
                    break;
                }
                case 'a':
                {
                    symbol = "THAT";
                    break;
                }
            }
        }
    }

    return symbol;
}

// Returns a push command (in Hack Assembly) based on a memory set and a value
char* push_command(char* memset, int value)
{
    char *symbol, *buff, *v;

    fprintf(stderr, "Starting execution of function push_command\n");
    symbol = get_symbol(memset);
    buff = malloc(1000 * sizeof(char));
    v = malloc(5*sizeof(char));

    buff[0] = '\0';

    sprintf(v, "@%i\n", value);

    // @value
    strcat(buff, v);
    strcat(buff, "D=A\n");


    // @Symbol
    strcat(buff, "@"); 
    strcat(buff, symbol);

    // A=D+M (goto location "value" of memory the given segment)
    strcat(buff, "\nA=D+M\n");

    // D=M
    strcat(buff, "D=M\n");

    /*
    * @SP
    * A=M
    * M=D
    * @SP
    * M=M+1
    */
    strcat(buff, "@SP\nA=M\nM=D\n@SP\nM=M+1");


    return buff;
}

// Returns a pop command based on the value and memory set
char* pop_command(char* memset, int value)
{
    char *buff, *symbol, *v;
    buff = malloc(900 * sizeof(char));
    v = malloc(5*sizeof(char));
    symbol = get_symbol(memset);

    sprintf(v, "@%i\n", value);

    // @SP
    // M=M-1
    strcat(buff, "@SP\n");
    strcat(buff, "M=M-1\n");

    // @value
    strcat(buff, v);
    strcat(buff, "D=A\n");

    /*
    * @symbol
    * D=M+D
    * @temp
    * M=D
    */
    strcat(buff, "@");
    strcat(buff, symbol);
    strcat(buff, "\nD=M+D\n@temp\nM=D\n");

    /*
    * @SP
    * M=M-1
    * A=M
    * D=M
    * @temp
    * A=M
    * M=D
    **/
    strcat(buff, "@SP\nM=M-1\nA=M\nD=M\n@temp\nA=M\nM=D\n");

    return buff;
}


void add_all_commands(TREE* root)
{
    // push/pop local/argument/this/that
    add_command(root, "local", push_command, pop_command);
    add_command(root, "argument", push_command, pop_command);
    add_command(root, "this", push_command, pop_command);
    add_command(root, "that", push_command, pop_command);

    return;

}
