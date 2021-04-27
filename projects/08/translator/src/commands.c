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

char* get_operand(char* op)
{
    switch (op[0])
    {
        case 'a':
            switch (op[1])
            {
                case 'd':
                    return "+";
                case 'n':
                    return "&";
            }
        case 's':
            return "-";
        case 'o':
            return "|";
        case 'e':
            return "JEQ\n";
        case 'g':
            return "JGT\n";
        case 'l':
            return "JLT\n";
        case 'n':
            switch (op[1])
            {
                case 'o':
                    return "!";
                case 'e':
                    return "-";
            }
    }

    return NULL;
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

char* constant_push(char* memset, int value)
{
    char* v, *buff;

    v = malloc(7*sizeof(char));
    sprintf(v, "@%i\n", value);

    buff = malloc(1000*sizeof(char));
    buff[0] = '\0';

    /*
    * @value
    * D=A
    **/
    strcat(buff, v);
    strcat(buff, "D=A\n");

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

char* push_static(char* memset, int value)
{
    char *v, *buff;

    v = malloc(7*sizeof(char));
    buff = malloc(1000*sizeof(char));

    buff[0] = '\0';

    sprintf(v, "@Static.%i\n", value);

    /*
    @Static.value
    D=M
    */
    strcat(buff, v);
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

char* pop_static(char* memset, int val)
{
    char *v, *buff;

    v = malloc(7*sizeof(char));
    buff = malloc(1000*sizeof(char));

    sprintf(v, "@Static.%i\n", val);

    /*
    * @SP
    * M=M-1
    * A=M
    * D=M
    * @Static.value
    * M=D
    */

    strcat(buff, "@SP\nM=M-1\nA=M\nD=M\n");
    strcat(buff, v);
    strcat(buff, "M=D\n");

    return buff;

}

char* push_temp(char* memset, int value)
{
    char *v, *buff;

    v = malloc(7*sizeof(char));
    buff = malloc(1000*sizeof(char));

    sprintf(v, "@%i\n", value+5);
    buff[0] = '\0';

    /*
    * @(value+5)
    * D=M
    */
    strcat(buff, v);
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

char* pop_temp(char* memset, int value)
{
    char *v, *buff;

    v = malloc(7*sizeof(char));
    sprintf(v, "@%i\n", value+5);

    buff = malloc(1000*sizeof(char));

    /*
    * @SP
    * M=M-1
    * A=M
    * D=M
    */
    strcat(buff, "@SP\nM=M-1\nA=M\nD=M\n");

    /*
    * @(value+5)
    * M=D
    */
    strcat(buff, v);
    strcat(buff, "M=D\n");


    return buff;


}

char* push_pointer(char* memset, int value)
{
    char *v, *buff;

    v = (value)? "@THAT\n" : "@THIS\n";

    buff = malloc(1000*sizeof(char));
    buff[0] = '\0';

    /*
    * @(THIS/THAT)
    * D=A
    */
    strcat(buff, v);
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

char* pop_pointer(char* memset, int value)
{
    char *v, *buff;
    v = (value)? "@THAT\n" : "@THIS\n";
    buff = malloc(1000*sizeof(char));
    buff[0] = '\0';

    /*
    * @SP
    * M=M-1
    * A=M
    * D=M
    */
    strcat(buff, "@SP\nM=M-1\nA=M\nD=M\n");


    /*
    * @(THIS/THAT)
    * M=D
    */
    strcat(buff, v);
    strcat(buff, "M=D\n");

    return buff;

}

// add, sub, and, or
char* arithmetic1(char* cmd)
{

    char* buff;

    buff = malloc(1000*sizeof(char));

    // pop x
    /*
    * @SP
    * M=M-1
    * A=M
    * D=M
    */
    strcat(buff, "@SP\nM=M-1\nA=M\nD=M\n");

    // pop y
    /*
    *
    * @SP
    * M=M-1
    * A=M
    */
    strcat(buff, "@SP\nM=M-1\nA=M\nM=M");
    strcat(buff, get_operand(cmd));
    strcat(buff, "D\n@SP\nM=M+1\n");

    return buff;

}

// eq, gt, lt
char* arithmetic2(char* cmd)
{

    char* buff, *set, *dest, *set_ref, *dest_ref;

    dest = malloc(70*sizeof(char));
    dest_ref = malloc(70*sizeof(char));
    set_ref = malloc(70*sizeof(char));
    set = malloc(70*sizeof(char));

    buff = malloc(1000*sizeof(char));
    // pop x
    /*
    * @SP
    * M=M-1
    * A=M
    * D=M
    */

    strcat(buff, "@SP\nM=M-1\nA=M\nD=M\n");

    // pop y
    /*
    *
    * @SP
    * M=M-1
    * A=M
    */

    sprintf(dest, "(DEST_%i)\n", cps);
    sprintf(dest_ref, "@DEST_%i\n", cps);
    sprintf(set, "(SET_%i)\n", cps);
    sprintf(set_ref, "@SET_%i\n", cps);

    strcat(buff, "@SP\nM=M-1\nA=M\nD=M-D\n");
    strcat(buff, set_ref);
    strcat(buff, "D;");
    strcat(buff, get_operand(cmd));
    strcat(buff, "D=0\n");
    strcat(buff, dest_ref);
    strcat(buff, "0;JMP\n");

    strcat(buff, set);
    strcat(buff, "D=-1\n");
    strcat(buff, dest_ref);
    strcat(buff, "0;JMP\n");

    /*
    * @SP
    * A=M
    * M=D
    * @SP
    * M=M+1
    */
    strcat(buff, dest);
    strcat(buff, "@SP\nA=M\nM=D\n@SP\nM=M+1\n");

    cps++;

    return  buff;

}

char* arithmetic3(char* cmd)
{
    char* buff;

    buff = malloc(1000*sizeof(char));
    buff[0] = '\0';

    strcat(buff, "@SP\nM=M-1\nA=M\nM=");
    strcat(buff, get_operand(cmd));
    strcat(buff, "M\n@SP\nM=M+1\n");
    return buff;

}

char* arithmetic_manager(char* cmd)
{
    char* r;

    switch (cmd[0])
    {
        case 'a':
        case 's':
        case 'o':
            r = arithmetic1(cmd);
            break;
        case 'e':
        case 'g':
        case 'l':
            r = arithmetic2(cmd);
            break;
        case 'n':
            r = arithmetic3(cmd);
            break;
        default:
            r = NULL;
    }

    return r;
}

void add_all_commands(TREE* root)
{
    // push/pop local/argument/this/that (val)
    add_command(root, "local", push_command, pop_command);
    add_command(root, "argument", push_command, pop_command);
    add_command(root, "this", push_command, pop_command);
    add_command(root, "that", push_command, pop_command);

    // pop constant (val)
    add_command(root, "constant", constant_push, NULL);

    // push/pop static (add)
    add_command(root, "static", push_static, pop_static);

    // push/pop temp (add)
    add_command(root, "temp", push_temp, pop_temp);

    // push/pop pointer (0/1)
    add_command(root, "pointer", push_pointer, pop_pointer);

    return;

}
