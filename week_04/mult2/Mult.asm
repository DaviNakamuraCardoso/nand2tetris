// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
//
// This program only needs to handle arguments that satisfy
// R0 >= 0, R1 >= 0, and R0*R1 < 32768.
// n = R0
// m = R1
// result = 0
// for (i = 0; i < n; i++) {
// result += m;
// }
// R2 = result
//

    // n = R0
    @R0
    D=M
    @n
    M=D

    // m = R1
    @R1
    D=M
    @m
    M=D

    // result = 0
    @R0
    D=A
    @result
    M=D

    // i = 0
    @R0
    D=A
    @i
    M=D

    // for (i - n > 0)
    (LOOP)
    @i
    D=M
    @n
    D=D-M
    @ENDFOR
    D;JEQ

    // result += m
    @m
    D=M
    @result
    M=M+D

    // i++
    @i
    M=M+1

    @LOOP
    0;JMP

    // R2 = result
    (ENDFOR)
    @result
    D=M
    @R2
    M=D

    // end of program
    (END)
    @END
    0;JMP
