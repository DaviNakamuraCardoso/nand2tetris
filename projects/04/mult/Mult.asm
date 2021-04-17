// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
//
// This program only needs to handle arguments that satisfy
// R0 >= 0, R1 >= 0, and R0*R1 < 32768.
// r2 = 0;
// product = r1;
// n = r0
// for (i = 0; i < n; i++) {
// product = product + r1;
//}
// r2 = product

    @R2     // r2 = 0
    M=0

    @R1     // product = r1
    D=M

    @product
    M=D

    @R0     // n = r0
    D=M

    @n
    M=D

    @i      // i = 1
    M=1

    (LOOP) // for
    @i      // if i - n == 0 goto STOP
    D=M

    @n
    D=M-D

    @STOP
    D;JEQ

    @R1
    D=M // product = product + r1

    @product
    M=M+D

    @i  // i++
    M=M+1

    @LOOP   // goto LOOP
    0;JMP

    (STOP)
    @product        // r2 = product
    D=M

    @R2
    M=D

    (END)
    @END
    0;JMP
