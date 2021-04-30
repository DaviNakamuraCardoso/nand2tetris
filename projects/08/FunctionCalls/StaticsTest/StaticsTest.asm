
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

// // File name: projects/08/FunctionCalls/StaticsTest/Class1.vm

// 

// // Stores two supplied arguments in static[0] and static[1].

// function Class1.set 0

(Class1.set)
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
// pop static 0

@SP
M=M-1
A=M
D=M
@Static.0
M=D

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
// pop static 1

@SP
M=M-1
A=M
D=M
@Static.1
M=D

// push constant 0

@0
D=A
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

// 

// // Returns static[0] - static[1].

// function Class1.get 0

(Class1.get)
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

// push static 0

@Static.0
D=M
@SP
A=M
M=D
@SP
M=M+1
// push static 1

@Static.1
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

// // This file is part of www.nand2tetris.org

// // and the book "The Elements of Computing Systems"

// // by Nisan and Schocken, MIT Press.

// // File name: projects/08/FunctionCalls/StaticsTest/Class2.vm

// 

// // Stores two supplied arguments in static[0] and static[1].

// function Class2.set 0

(Class2.set)
@R13
M=0
D=0
(PUSH_ZEROS.2)
@0
D=A-D
@END_PUSH_ZEROS.2
D;JLE
@SP
A=M
M=0
@SP
M=M+1
@R13
M=M+1
D=M
@PUSH_ZEROS.2
0;JMP
(END_PUSH_ZEROS.2)

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
// pop static 0

@SP
M=M-1
A=M
D=M
@Static.0
M=D

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
// pop static 1

@SP
M=M-1
A=M
D=M
@Static.1
M=D

// push constant 0

@0
D=A
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

// 

// // Returns static[0] - static[1].

// function Class2.get 0

(Class2.get)
@R13
M=0
D=0
(PUSH_ZEROS.3)
@0
D=A-D
@END_PUSH_ZEROS.3
D;JLE
@SP
A=M
M=0
@SP
M=M+1
@R13
M=M+1
D=M
@PUSH_ZEROS.3
0;JMP
(END_PUSH_ZEROS.3)

// push static 0

@Static.0
D=M
@SP
A=M
M=D
@SP
M=M+1
// push static 1

@Static.1
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

// // This file is part of www.nand2tetris.org

// // and the book "The Elements of Computing Systems"

// // by Nisan and Schocken, MIT Press.

// // File name: projects/08/FunctionCalls/StaticsTest/Sys.vm

// 

// // Tests that different functions, stored in two different

// // class files, manipulate the static segment correctly.

// function Sys.init 0

(Sys.init)
@R13
M=0
D=0
(PUSH_ZEROS.4)
@0
D=A-D
@END_PUSH_ZEROS.4
D;JLE
@SP
A=M
M=0
@SP
M=M+1
@R13
M=M+1
D=M
@PUSH_ZEROS.4
0;JMP
(END_PUSH_ZEROS.4)

// push constant 6

@6
D=A
@SP
A=M
M=D
@SP
M=M+1
// push constant 8

@8
D=A
@SP
A=M
M=D
@SP
M=M+1
// call Class1.set 2

@Class1.set$ret.1
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
@2
D=D+A
@SP
D=M-D
@ARG
M=D
@SP
D=M
@LCL
M=D
@Class1.set
0;JMP
(Class1.set$ret.1)

// pop temp 0 // Dumps the return value

@SP
M=M-1
A=M
D=M
@5
M=D

// call Class1.get 0

@Class1.get$ret.2
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
@Class1.get
0;JMP
(Class1.get$ret.2)

// push constant 23

@23
D=A
@SP
A=M
M=D
@SP
M=M+1
// push constant 15

@15
D=A
@SP
A=M
M=D
@SP
M=M+1
// call Class2.set 2

@Class2.set$ret.3
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
@2
D=D+A
@SP
D=M-D
@ARG
M=D
@SP
D=M
@LCL
M=D
@Class2.set
0;JMP
(Class2.set$ret.3)

// pop temp 0 // Dumps the return value

@SP
M=M-1
A=M
D=M
@5
M=D

// call Class2.get 0

@Class2.get$ret.4
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
@Class2.get
0;JMP
(Class2.get$ret.4)

// label WHILE

(WHILE)
// goto WHILE

@WHILE
0;JMP

