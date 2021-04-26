// push constant 81

@81
D=A
@SP
A=M
M=D
@SP
M=M+1
// neg

@SP
M=M-1
A=M
M=-M
@SP
M=M+1

// push constant 91

@91
D=A
@SP
A=M
M=D
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
