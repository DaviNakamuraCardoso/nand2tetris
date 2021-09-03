// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed.
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.


// while (1) {
    // key = KBD
    // color = white
    // if (key > 0)  {
    // color = black
    // }
    // screen_start = SCREEN
    //for (i = screen_start; i < screen_end; i++) {
        //@i
        //A=M
        //M=color
    //}
// }

    (MAIN_LOOP)
    // key = KBD
    @KBD
    D=M
    @key
    M=D

    // color = 0 (white)
    @R0
    D=A
    @color
    M=D

    @key
    D=M
    // if (key > 0) then color = -1 (black)
    @ENDIF
    D;JEQ

    @color
    M=-1

    (ENDIF)

    // i = screen
    @SCREEN
    D=A

    @i
    M=D

    // for (i = screen_start; i < screen_end; i++) {
    (FOR)
    @i
    D=M
    @KBD
    D=A-D

    @ENDFOR
    D;JLE

    @color
    D=M

    @i
    A=M
    M=D

    // i++
    @i
    M=M+1

    @FOR
    0;JMP

    (ENDFOR)

    @MAIN_LOOP
    0;JMP
