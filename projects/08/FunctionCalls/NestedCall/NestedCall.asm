
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

// // Sys.vm for NestedCall test.

// 

// // Sys.init()

// //

// // Calls Sys.main() and stores return value in temp 1.

// // Does not return.  (Enters infinite loop.)

// 

// function Sys.init 0

(Sys.init)
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

// push constant 4000	// test THIS and THAT context save

@4000
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

// push constant 5000

@5000
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

// call Sys.main 0

@Sys.main$ret.1
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
@Sys.main
0;JMP
(Sys.main$ret.1)

// pop temp 1

@SP
M=M-1
A=M
D=M
@6
M=D

// label LOOP

(LOOP)
// goto LOOP

@LOOP
0;JMP

// 

// // Sys.main()

// //

// // Sets locals 1, 2 and 3, leaving locals 0 and 4 unchanged to test

// // default local initialization to 0.  (RAM set to -1 by test setup.)

// // Calls Sys.add12(123) and stores return value (135) in temp 0.

// // Returns local 0 + local 1 + local 2 + local 3 + local 4 (456) to confirm

// // that locals were not mangled by function call.

// 

// function Sys.main 5

(Sys.main)
@R13
M=0
D=0
(PUSH_ZEROS.1)
@5
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

// push constant 4001

@4001
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

// push constant 5001

@5001
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

// push constant 200

@200
D=A
@SP
A=M
M=D
@SP
M=M+1
// pop local 1

@1
D=A
@LCL
D=M+D
@R14
M=D
@SP
M=M-1
A=M
D=M
@R14
A=M
M=D

// push constant 40

@40
D=A
@SP
A=M
M=D
@SP
M=M+1
// pop local 2

@2
D=A
@LCL
D=M+D
@R14
M=D
@SP
M=M-1
A=M
D=M
@R14
A=M
M=D

// push constant 6

@6
D=A
@SP
A=M
M=D
@SP
M=M+1
// pop local 3

@3
D=A
@LCL
D=M+D
@R14
M=D
@SP
M=M-1
A=M
D=M
@R14
A=M
M=D

// push constant 123

@123
D=A
@SP
A=M
M=D
@SP
M=M+1
// call Sys.add12 1

@Sys.add12$ret.2
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
@Sys.add12
0;JMP
(Sys.add12$ret.2)

// pop temp 0

@SP
M=M-1
A=M
D=M
@5
M=D

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
// push local 2

@2
D=A
@LCL
A=D+M
D=M
@SP
A=M
M=D
@SP
M=M+1
// push local 3

@3
D=A
@LCL
A=D+M
D=M
@SP
A=M
M=D
@SP
M=M+1
// push local 4

@4
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

// // Sys.add12(int n)

// //

// // Returns n+12.

// 

// function Sys.add12 0

(Sys.add12)
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

// push constant 4002

@4002
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

// push constant 5002

@5002
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
// push constant 12

@12
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

