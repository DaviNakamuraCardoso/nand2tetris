// // This file is part of www.nand2tetris.org

// // and the book "The Elements of Computing Systems"

// // by Nisan and Schocken, MIT Press.

// // File name: projects/07/StackArithmetic/StackTest/StackTest.vm

// 

// // Executes a sequence of arithmetic and logical operations

// // on the stack. 

// push constant 17

@17
D=A
@SP
A=M
M=D
@SP
M=M+1
// push constant 17

@17
D=A
@SP
A=M
M=D
@SP
M=M+1
// eq

@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
D=M-D
@SET_0
D;JEQ
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

// push constant 17

@17
D=A
@SP
A=M
M=D
@SP
M=M+1
// push constant 16

@16
D=A
@SP
A=M
M=D
@SP
M=M+1
// eq

@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
D=M-D
@SET_1
D;JEQ
D=0
@DEST_1
0;JMP
(SET_1)
D=-1
@DEST_1
0;JMP
(DEST_1)
@SP
A=M
M=D
@SP
M=M+1

// push constant 16

@16
D=A
@SP
A=M
M=D
@SP
M=M+1
// push constant 17

@17
D=A
@SP
A=M
M=D
@SP
M=M+1
// eq

@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
D=M-D
@SET_2
D;JEQ
D=0
@DEST_2
0;JMP
(SET_2)
D=-1
@DEST_2
0;JMP
(DEST_2)
@SP
A=M
M=D
@SP
M=M+1

// push constant 892

@892
D=A
@SP
A=M
M=D
@SP
M=M+1
// push constant 891

@891
D=A
@SP
A=M
M=D
@SP
M=M+1
// lt

@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
D=M-D
@SET_3
D;JLT
D=0
@DEST_3
0;JMP
(SET_3)
D=-1
@DEST_3
0;JMP
(DEST_3)
@SP
A=M
M=D
@SP
M=M+1

// push constant 891

@891
D=A
@SP
A=M
M=D
@SP
M=M+1
// push constant 892

@892
D=A
@SP
A=M
M=D
@SP
M=M+1
// lt

@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
D=M-D
@SET_4
D;JLT
D=0
@DEST_4
0;JMP
(SET_4)
D=-1
@DEST_4
0;JMP
(DEST_4)
@SP
A=M
M=D
@SP
M=M+1

// push constant 891

@891
D=A
@SP
A=M
M=D
@SP
M=M+1
// push constant 891

@891
D=A
@SP
A=M
M=D
@SP
M=M+1
// lt

@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
D=M-D
@SET_5
D;JLT
D=0
@DEST_5
0;JMP
(SET_5)
D=-1
@DEST_5
0;JMP
(DEST_5)
@SP
A=M
M=D
@SP
M=M+1

// push constant 32767

@32767
D=A
@SP
A=M
M=D
@SP
M=M+1
// push constant 32766

@32766
D=A
@SP
A=M
M=D
@SP
M=M+1
// gt

@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
D=M-D
@SET_6
D;JGT
D=0
@DEST_6
0;JMP
(SET_6)
D=-1
@DEST_6
0;JMP
(DEST_6)
@SP
A=M
M=D
@SP
M=M+1

// push constant 32766

@32766
D=A
@SP
A=M
M=D
@SP
M=M+1
// push constant 32767

@32767
D=A
@SP
A=M
M=D
@SP
M=M+1
// gt

@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
D=M-D
@SET_7
D;JGT
D=0
@DEST_7
0;JMP
(SET_7)
D=-1
@DEST_7
0;JMP
(DEST_7)
@SP
A=M
M=D
@SP
M=M+1

// push constant 32766

@32766
D=A
@SP
A=M
M=D
@SP
M=M+1
// push constant 32766

@32766
D=A
@SP
A=M
M=D
@SP
M=M+1
// gt

@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
D=M-D
@SET_8
D;JGT
D=0
@DEST_8
0;JMP
(SET_8)
D=-1
@DEST_8
0;JMP
(DEST_8)
@SP
A=M
M=D
@SP
M=M+1

// push constant 57

@57
D=A
@SP
A=M
M=D
@SP
M=M+1
// push constant 31

@31
D=A
@SP
A=M
M=D
@SP
M=M+1
// push constant 53

@53
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

// push constant 112

@112
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

// neg

@SP
M=M-1
A=M
M=-M
@SP
M=M+1

// and

@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
M=M&D
@SP
M=M+1

// push constant 82

@82
D=A
@SP
A=M
M=D
@SP
M=M+1
// or

@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
M=M|D
@SP
M=M+1

// not

@SP
M=M-1
A=M
M=!M
@SP
M=M+1

(END)
@END
0;JMP
