
// _______________________ Start of function call ___________________ //


    // Push the return address
    @Foo$ret.1
    D=A
    @SP
    A=M
    M=D
    @SP
    M=M+1

    // Saves the local of the caller
    @LCL
    D=M
    @SP
    A=M
    M=D
    @SP
    M=M+1

    // Saves the arg of the caller
    @ARG
    D=M
    @SP
    A=M
    M=D
    @SP
    M=M+1

    // Saves the "THIS" of the caller
    @THIS
    D=M
    @SP
    A=M
    M=D
    @SP
    M=M+1

    // Saves the "THAT" of the caller
    @THAT
    D=M
    @SP
    A=M
    M=D
    @SP
    M=M+1

    // Repositions arg
    @5
    D=A
    @2
    D=D+A
    @SP
    D=M-D
    @ARG
    M=D

    // Repositions LCL (LCL = SP)
    @SP
    D=M
    @LCL
    M=D

    @Foo
    0;JMP

    // Return address
    (Foo$ret.1)

// ____________________ End of function call ___________________ //

// ________________ Start of function definition _______________ //

    // label
    (Foo)

    // repeat nvars times push 0
    @tmp
    M=0
    (PUSH_ZEROS)
    @SP
    A=M
    M=0
    @SP
    M=M+1
    @tmp
    M=M+1
    D=M
    @2
    D=A-D
    @PUSH_ZEROS
    D;JGT

// __________________ End of function definition _______________ //

// ___________________ Start of function return _____________ //

    // endFrame = LCL
    @LCL
    D=M
    @endFrame
    M=D

    // retAddr = *(endFrame - 5)
    @5
    D=A
    @endFrame
    D=M-D
    A=D
    D=M
    @retAddr
    M=D

    // ARG = pop()
    @SP
    M=M-1
    A=M
    D=M
    @ARG
    A=M
    M=D
    @ARG
    D=M
    @SP
    M=D+1

    // THAT is *(endFrame -1)
    @1
    D=A
    @endFrame
    D=M-D
    @THAT
    M=D

    // THIS is *(endFrame - 2)
    @2
    D=A
    @endFrame
    D=M-D
    @THIS
    M=D

    // ARG is *(endFrame - 3)
    @3
    D=A
    @endFrame
    D=M-D
    @ARG
    M=D

    // LCL is *(endFrame - 4)
    @4
    D=A
    @endFrame
    D=M-D
    @LCL
    M=D

    @retAddr
    A=M
    0;JMP
