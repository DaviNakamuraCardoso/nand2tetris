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

// Put your code here.
// while (1){
//    input = keyboard[];
//
//    if (input > 0)
//    {
//      color = -1; (black)
//
//    }
//    else {
//      color = 0; (white)
//   }
//
//    rows = 16
//    cols = 32
//    counter = 0
//    for (i = 0; i < rows; i++) {
//        for (j = 0; i < cols; j++) {
//          Screen[counter] = color;
//          counter += j + i
//      }
//   }
//}
//

    (LOOP)                      // while (1)

    @KBD                        // input = key
    D=M

    @input
    M=D

    @SCREEN                     // counter = screen[0]
    D=A

    @counter
    M=D

    @input
    D=M

    @IF
    M=0

    @IF                           // if input > 0
    D;JEQ
    @ELSE
    0;JMP

    (IF)
    @color                        // color = 0 (white)
    M=0
    @ENDIF
    0;JMP

    (ELSE)                        // color = -1 (black)
    @color
    M=-1

    @ENDIF
    0;JMP

    (ENDIF)

    @i                             // i = 0
    M=0

    @8160                           // rows = 8160
    D=A

    @rows
    M=D

    @ENDFOR
    M=1

    (FOR)   // if i == rows end loop

    @i
    D=M

    @rows
    D=D-M

    @ENDFOR
    D;JEQ


    @color
    D=M

    @counter
    A=M
    M=D

    @i      // i++
    M=M+1

    @counter
    M=M+1

    @FOR
    0;JMP
    (ENDFOR)

    @LOOP   // END
    0;JMP
