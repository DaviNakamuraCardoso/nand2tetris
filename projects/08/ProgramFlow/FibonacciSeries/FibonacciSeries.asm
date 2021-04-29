
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
// // This file is part of www.nand2tetris.org

// // and the book "The Elements of Computing Systems"

// // by Nisan and Schocken, MIT Press.

// // File name: projects/08/ProgramFlow/FibonacciSeries/FibonacciSeries.vm

// 

// // Puts the first argument[0] elements of the Fibonacci series

// // in the memory, starting in the address given in argument[1].

// // Argument[0] and argument[1] are initialized by the test script 

// // before this code starts running.

// 

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
// pop pointer 1           // that = argument[1]

@SP
M=M-1
A=M
D=M
@THAT
M=D

// 

// push constant 0

@0
D=A
@SP
A=M
M=D
@SP
M=M+1
// pop that 0              // first element in the series = 0

@0
D=A
@THAT
D=M+D
@temp
M=D
@SP
M=M-1
A=M
D=M
@temp
A=M
M=D

// push constant 1

@1
D=A
@SP
A=M
M=D
@SP
M=M+1
// pop that 1              // second element in the series = 1

@1
D=A
@THAT
D=M+D
@temp
M=D
@SP
M=M-1
A=M
D=M
@temp
A=M
M=D

// 

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

// pop argument 0          // num_of_elements -= 2 (first 2 elements are set)

@0
D=A
@ARG
D=M+D
@temp
M=D
@SP
M=M-1
A=M
D=M
@temp
A=M
M=D

// 

// label MAIN_LOOP_START

(MAIN_LOOP_STAR)
// 

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
// if-goto COMPUTE_ELEMENT // if num_of_elements > 0, goto COMPUTE_ELEMENT

@SP
M=M-1
A=M
D=M
@COMPUTE_ELEMENT
D;JNE

// goto END_PROGRAM        // otherwise, goto END_PROGRAM

@END_PROGRAM$ret.0
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
@END_PROGRAM
0;JMP
(END_PROGRAM$ret.0)

// 

// label COMPUTE_ELEMENT

(COMPUTE_ELEMEN)
// 

// push that 0

@0
D=A
@THAT
A=D+M
D=M
@SP
A=M
M=D
@SP
M=M+1
// push that 1

@1
D=A
@THAT
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

// pop that 2              // that[2] = that[0] + that[1]

@2
D=A
@THAT
D=M+D
@temp
M=D
@SP
M=M-1
A=M
D=M
@temp
A=M
M=D

// 

// push pointer 1

@THAT
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

// pop pointer 1           // that += 1

@SP
M=M-1
A=M
D=M
@THAT
M=D

// 

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

// pop argument 0          // num_of_elements--

@0
D=A
@ARG
D=M+D
@temp
M=D
@SP
M=M-1
A=M
D=M
@temp
A=M
M=D

// 

// goto MAIN_LOOP_START

@MAIN_LOOP_START
0;JMP

// 

// label END_PROGRAM

(END_PROGRA)
(END)
@END
0;JMP
