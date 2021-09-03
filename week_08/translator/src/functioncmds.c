#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <functioncmds.h>

int calls = 0;
int zeros = 0;

// Implements a function call in Hack Assembly
char* command_call(char* function_name, int nargs)
{
    char* buff, *ret, *argcount;
    buff = malloc(1000*sizeof(char));
    ret = malloc(100*sizeof(char));
    argcount = malloc(100*sizeof(char));


    buff[0] = '\0';

    // Defines a function return label
    sprintf(ret, "%s$ret.%i", function_name, calls);
    calls++;

    sprintf(argcount, "@%i\n", nargs);

    /*
        // Push the return address
        @Foo$ret.1
        D=A
        @SP
        A=M
        M=D
        @SP
        M=M+1

    */
    strcat(buff, "@");
    strcat(buff, ret);
    strcat(buff, "\nD=A\n@SP\nA=M\nM=D\n@SP\nM=M+1\n");

    /*
        // Saves the local of the caller
        @LCL
        D=M
        @SP
        A=M
        M=D
        @SP
        M=M+1
    */
    strcat(buff, "@LCL\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n");


    /*
        // Saves the arg of the caller
        @ARG
        D=M
        @SP
        A=M
        M=D
        @SP
        M=M+1
    */

    strcat(buff, "@ARG\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n");
    /*

        // Saves the "THIS" of the caller
        @THIS
        D=M
        @SP
        A=M
        M=D
        @SP
        M=M+1
    */

    strcat(buff, "@THIS\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n");

    /*
        // Saves the "THAT" of the caller
        @THAT
        D=M
        @SP
        A=M
        M=D
        @SP
        M=M+1
    */
    strcat(buff, "@THAT\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n");

    /*
        // Repositions arg
        @5
        D=A
        @nargs
        D=D+A
        @SP
        D=M-D
        @ARG
        M=D
    */
    strcat(buff, "@5\nD=A\n");
    strcat(buff, argcount);
    strcat(buff, "D=D+A\n@SP\nD=M-D\n@ARG\nM=D\n");

    /*
        // Repositions LCL (LCL = SP)
        @SP
        D=M
        @LCL
        M=D
    */
    strcat(buff, "@SP\nD=M\n@LCL\nM=D\n");
    /*
        @Foo
        0;JMP
        // Return address
        (Foo$ret.1)
    */
    strcat(buff, "@");
    strcat(buff, function_name);
    strcat(buff, "\n0;JMP\n(");
    strcat(buff, ret);
    strcat(buff, ")\n");

    return buff;
}

// Implements a function definition in Hack Assembly
char* command_function(char* function_name, int locals)
{

    char* buff, *push_zeros, *nlocals, *zeros_end;

    // buffer
    buff = malloc(1000*sizeof(char));
    buff[0] = '\0';

    // Push zeros label
    push_zeros = malloc(100*sizeof(char));
    zeros_end = malloc(100*sizeof(char));

    sprintf(zeros_end, "END_PUSH_ZEROS.%i", zeros);
    sprintf(push_zeros, "PUSH_ZEROS.%i", zeros);
    zeros++;

    // Number of locals
    nlocals = malloc(100*sizeof(char));
    sprintf(nlocals, "@%i\n", locals);


    /*
        // label
        (Foo)

    */

    strcat(buff, "(");
    strcat(buff, function_name);
    strcat(buff, ")\n");


    /*
        // repeat nvars times push 0
        @tmp
        M=0
        (PUSH_ZEROS)
    */
    strcat(buff, "@R13\nM=0\nD=0\n(");
    strcat(buff, push_zeros);
    strcat(buff, ")\n");

    strcat(buff, nlocals);
    strcat(buff, "D=A-D\n@");
    strcat(buff, zeros_end);
    strcat(buff, "\nD;JLE\n");

    /*
        @SP
        A=M
        M=0
        @SP
        M=M+1
        @tmp
        M=M+1
        D=M
    */
    strcat(buff, "@SP\nA=M\nM=0\n@SP\nM=M+1\n@R13\nM=M+1\nD=M\n");

    strcat(buff, "@");
    strcat(buff, push_zeros);
    strcat(buff, "\n0;JMP\n");

    strcat(buff, "(");
    strcat(buff, zeros_end);
    strcat(buff, ")\n");


    return buff;

}

// Implements a function return in Hack Assembly
char* command_return(void)
{
    char* buff;

    buff = malloc(1000*sizeof(char));
    buff[0] = '\0';


    /*
        // endFrame = LCL
        @LCL
        D=M
        @endFrame
        M=D
    */
    strcat(buff, "@LCL\nD=M\n@endFrame\nM=D\n");

    /*

        // retAddr = *(endFrame - 5)
        @5
        D=A
        @endFrame
        D=M-D
        A=D
        D=M
        @retAddr
        M=D

    */
    strcat(buff, "@5\nD=A\n@endFrame\nD=M-D\nA=D\nD=M\n@retAddr\nM=D\n");

    /*
        // *ARG = pop()
        @SP
        M=M-1
        A=M
        D=M
        @ARG
        A=M
        M=D
    */
    strcat(buff, "@SP\nM=M-1\nA=M\nD=M\n@ARG\nA=M\nM=D\n");

    /*

        // SP = ARG+1
        @ARG
        D=M
        @1
        D=D+A
        @SP
        M=D
    */
    strcat(buff, "@ARG\nD=M\n@SP\nM=D+1\n");


    /*

        // THAT is *(endFrame -1)
        @1
        D=A
        @endFrame
        D=M-D
        A=D
        D=M
        @THAT
        M=D
    */
    strcat(buff, "@1\nD=A\n@endFrame\nD=M-D\nA=D\nD=M\n@THAT\nM=D\n");

    /*
        // THIS is *(endFrame - 2)
        @2
        D=A
        @endFrame
        D=M-D
        A=D
        D=M
        @THIS
        M=D
    */
    strcat(buff, "@2\nD=A\n@endFrame\nD=M-D\nA=D\nD=M\n@THIS\nM=D\n");

    /*
        // ARG is *(endFrame - 3)
        @3
        D=A
        @endFrame
        D=M-D
        A=D
        D=M
        @ARG
        M=D
    */

    strcat(buff, "@3\nD=A\n@endFrame\nD=M-D\nA=D\nD=M\n@ARG\nM=D\n");

    /*

        // LCL is *(endFrame - 4)
        @4
        D=A
        @endFrame
        D=M-D
        A=D
        D=M
        @LCL
        M=D
    */

    strcat(buff, "@4\nD=A\n@endFrame\nD=M-D\nA=D\nD=M\n@LCL\nM=D\n");

    /*
        @retAddr
        A=M
        0;JMP
    */
    strcat(buff, "@retAddr\nA=M\n0;JMP\n");

    return buff;
}


char* function_manager(char* cmd1, char* cmd2, char* cmd3)
{
    switch (cmd1[0])
    {
        case 'f':
            return command_function(cmd2, atoi(cmd3));
    }
    return command_call(cmd2, atoi(cmd3));
}

// Outputs a if-goto command based on a label
char* if_goto(char* label)
{
    char* buff;

    buff = malloc(1000*sizeof(char));
    buff[0] = '\0';

    /*
    * @SP
    * M=M-1
    * A=M
    * D=M
    * @label
    * D;JNE
    */

    strcat(buff, "@SP\nM=M-1\nA=M\nD=M\n@");
    strcat(buff, label);
    strcat(buff, "\nD;JNE\n");

    return buff;
}


// Outputs a goto command in Hack Assembly for a given label
char* command_goto(char* label)
{
    char* buff;

    buff = malloc(1000*sizeof(char));
    buff[0] = '\0';

    strcat(buff, "@");
    strcat(buff, label);
    strcat(buff, "\n0;JMP\n");


    return buff;
}

// Outputs a label in Hack Assembly
char* command_label(char* label)
{
    char* buff;

    buff = malloc(1000*sizeof(char));
    label[strlen(label)] = '\0';

    strcat(buff, "(");
    strcat(buff, label);
    strcat(buff, ")");

    return buff;
}

char* branch_manager(char* cmd1, char* cmd2)
{
    switch (cmd1[0])
    {
        case 'l':
            return command_label(cmd2);
        case 'i':
            return if_goto(cmd2);
    }

    return command_goto(cmd2);
}
