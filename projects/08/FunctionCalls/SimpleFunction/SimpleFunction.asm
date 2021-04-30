// // This file is part of www.nand2tetris.org

// // and the book "The Elements of Computing Systems"

// // by Nisan and Schocken, MIT Press.

// // File name: projects/08/FunctionCalls/SimpleFunction/SimpleFunction.vm

// 

// // Performs a simple calculation and returns the result.

// 

// function SimpleFunction.test 2

(SimpleFunction.test)
@tmp
M=0
(PUSH_ZEROS.0)
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
@PUSH_ZEROS.0
D;JGT

// push local 0

@0
D=A
@LCL
A=D+M
D=M
@SP
A=M
M=D
@SP
M=M+1
// push local 1

@1
D=A
@LCL
A=D+M
D=M
@SP
A=M
M=D
@SP
M=M+1
// add

@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
M=M+D
@SP
M=M+1

// not

@SP
M=M-1
A=M
M=!M
@SP
M=M+1

// push argument 0

@0
D=A
@ARG
A=D+M
D=M
@SP
A=M
M=D
@SP
M=M+1
// add

@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
M=M+D
@SP
M=M+1

// push argument 1

@1
D=A
@ARG
A=D+M
D=M
@SP
A=M
M=D
@SP
M=M+1
// sub

@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
M=M-D
@SP
M=M+1

// return

@LCL
D=M
@endFrame
M=D
@5
D=A
@endFrame
D=M-D
A=D
D=M
@retAddr
M=D
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
@1
D=A
@endFrame
D=M-D
A=D
D=M
@THAT
M=D
@2
D=A
@endFrame
D=M-D
A=D
D=M
@THIS
M=D
@3
D=A
@endFrame
D=M-D
A=D
D=M
@ARG
M=D
@4
D=A
@endFrame
D=M-D
A=D
D=M
@LCL
M=D
@retAddr
A=M
0;JMP

(END)
@END
0;JMP
