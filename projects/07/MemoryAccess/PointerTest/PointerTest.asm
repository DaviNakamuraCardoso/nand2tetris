// // This file is part of www.nand2tetris.org

// // and the book "The Elements of Computing Systems"

// // by Nisan and Schocken, MIT Press.

// // File name: projects/07/MemoryAccess/PointerTest/PointerTest.vm

// 

// // Executes pop and push commands using the 

// // pointer, this, and that segments.

// push constant 3030

@3030
D=A
@SP
A=M
M=D
@SP
M=M+1
// pop pointer 0

@SP
M=M-1
A=M
D=M
@THIS
M=D

// push constant 3040

@3040
D=A
@SP
A=M
M=D
@SP
M=M+1
// pop pointer 1

@SP
M=M-1
A=M
D=M
@THAT
M=D

// push constant 32

@32
D=A
@SP
A=M
M=D
@SP
M=M+1
// pop this 2

@2
D=A
@THIS
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

// push constant 46

@46
D=A
@SP
A=M
M=D
@SP
M=M+1
// pop that 6

@6
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

// push pointer 0

@THIS
D=M
@SP
A=M
M=D
@SP
M=M+1
// push pointer 1

@THAT
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

// push this 2

@2
D=A
@THIS
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

// push that 6

@6
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

(END)
@END
0;JMP
