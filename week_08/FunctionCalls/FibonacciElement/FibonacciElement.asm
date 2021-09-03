
@256
D=A
@SP
M=D
@300
D=A
@LCL
M=D
@400
D=A
@ARG
M=D
@3000
D=A
@THIS
M=D
@3010
D=A
@THAT
M=D
@Sys.init$ret.0
D=A
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@SP
A=M
M=D
@SP
M=M+1
@ARG
D=M
@SP
A=M
M=D
@SP
M=M+1
@THIS
D=M
@SP
A=M
M=D
@SP
M=M+1
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1
@5
D=A
@0
D=D+A
@SP
D=M-D
@ARG
M=D
@SP
D=M
@LCL
M=D
@Sys.init
0;JMP
(Sys.init$ret.0)

// // This file is part of www.nand2tetris.org

// // and the book "The Elements of Computing Systems"

// // by Nisan and Schocken, MIT Press.

// // File name: projects/08/FunctionCalls/FibonacciElement/Main.vm

// 

// // Computes the n'th element of the Fibonacci series, recursively.

// // n is given in argument[0].  Called by the Sys.init function 

// // (part of the Sys.vm file), which also pushes the argument[0] 

// // parameter before this code starts running.

// 

// function Main.fibonacci 0

(Main.fibonacci)
@R13
M=0
D=0
(PUSH_ZEROS.0)
@0
D=A-D
@END_PUSH_ZEROS.0
D;JLE
@SP
A=M
M=0
@SP
M=M+1
@R13
M=M+1
D=M
@PUSH_ZEROS.0
0;JMP
(END_PUSH_ZEROS.0)

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
// push constant 2

@2
D=A
@SP
A=M
M=D
@SP
M=M+1
// lt                     // checks if n<2

@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
D=M-D
@SET_0
D;JLT
D=0
@DEST_0
0;JMP
(SET_0)
D=-1
@DEST_0
0;JMP
(DEST_0)
@SP
A=M
M=D
@SP
M=M+1

// if-goto IF_TRUE

@SP
M=M-1
A=M
D=M
@IF_TRUE
D;JNE

// goto IF_FALSE

@IF_FALSE
0;JMP

// label IF_TRUE          // if n<2, return n

(IF_TRUE)
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

// label IF_FALSE         // if n>=2, returns fib(n-2)+fib(n-1)

(IF_FALSE)
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
// push constant 2

@2
D=A
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

// call Main.fibonacci 1  // computes fib(n-2)

@Main.fibonacci$ret.1
D=A
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@SP
A=M
M=D
@SP
M=M+1
@ARG
D=M
@SP
A=M
M=D
@SP
M=M+1
@THIS
D=M
@SP
A=M
M=D
@SP
M=M+1
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1
@5
D=A
@1
D=D+A
@SP
D=M-D
@ARG
M=D
@SP
D=M
@LCL
M=D
@Main.fibonacci
0;JMP
(Main.fibonacci$ret.1)

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
// push constant 1

@1
D=A
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

// call Main.fibonacci 1  // computes fib(n-1)

@Main.fibonacci$ret.2
D=A
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@SP
A=M
M=D
@SP
M=M+1
@ARG
D=M
@SP
A=M
M=D
@SP
M=M+1
@THIS
D=M
@SP
A=M
M=D
@SP
M=M+1
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1
@5
D=A
@1
D=D+A
@SP
D=M-D
@ARG
M=D
@SP
D=M
@LCL
M=D
@Main.fibonacci
0;JMP
(Main.fibonacci$ret.2)

// add                    // returns fib(n-1) + fib(n-2)

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

// // This file is part of www.nand2tetris.org

// // and the book "The Elements of Computing Systems"

// // by Nisan and Schocken, MIT Press.

// // File name: projects/08/FunctionCalls/FibonacciElement/Sys.vm

// 

// // Pushes a constant, say n, onto the stack, and calls the Main.fibonacii

// // function, which computes the n'th element of the Fibonacci series.

// // Note that by convention, the Sys.init function is called "automatically" 

// // by the bootstrap code.

// 

// function Sys.init 0

(Sys.init)
@R13
M=0
D=0
(PUSH_ZEROS.1)
@0
D=A-D
@END_PUSH_ZEROS.1
D;JLE
@SP
A=M
M=0
@SP
M=M+1
@R13
M=M+1
D=M
@PUSH_ZEROS.1
0;JMP
(END_PUSH_ZEROS.1)

// push constant 4

@4
D=A
@SP
A=M
M=D
@SP
M=M+1
// call Main.fibonacci 1   // computes the 4'th fibonacci element

@Main.fibonacci$ret.3
D=A
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@SP
A=M
M=D
@SP
M=M+1
@ARG
D=M
@SP
A=M
M=D
@SP
M=M+1
@THIS
D=M
@SP
A=M
M=D
@SP
M=M+1
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1
@5
D=A
@1
D=D+A
@SP
D=M-D
@ARG
M=D
@SP
D=M
@LCL
M=D
@Main.fibonacci
0;JMP
(Main.fibonacci$ret.3)

// label WHILE

(WHILE)
// goto WHILE              // loops infinitely

@WHILE
0;JMP

