# Nand2Tetris
## by Hebrew University of Jerusalem
Build a modern computer from Nand to Tetris (Project-Centered Course), with the
professors Noam Nisan and Shimon Shocken

### Week 01: Boolean Functions and Gate Logic
In this week we learned the concepts behind modern hardware: Boolean logic. We then built a total of 16 logic gates starting only with a **nand** gate, and then building more complex ones, like multiplexors and demultiplexors. 

#### Project: Chipset for the Hack Computer

-   [And16.hdl](./week_01/And16.hdl)
-   [And.hdl](./week_01/And.hdl)
-   [DMux4Way.hdl](./week_01/DMux4Way.hdl)
-   [DMux8Way.hdl](./week_01/DMux8Way.hdl)
-   [DMux.hdl](./week_01/DMux.hdl)
-   [Mux16.hdl](./week_01/Mux16.hdl)
-   [Mux4Way16.hdl](./week_01/Mux4Way16.hdl)
-   [Mux8Way16.hdl](./week_01/Mux8Way16.hdl)
-   [Mux.hdl](./week_01/Mux.hdl)
-   [Not16.hdl](./week_01/Not16.hdl)
-   [Not.hdl](./week_01/Not.hdl)
-   [Or16.hdl](./week_01/Or16.hdl)
-   [Or8Way.hdl](./week_01/Or8Way.hdl)
-   [Or.hdl](./week_01/Or.hdl)
-   [Xor.hdl](./week_01/Xor.hdl)

### Week 02: Arithmetic Logic Unit (ALU)
In this week we've learned about boolean arithmetic, comparison, half-adders, full-adders. We used those chips to build the heart of every modern CPU - the Arithmetic Logic Unit.

#### Project 02: ALU

-  [Add16.hdl](./week_02/Add16.hdl)
-  [ALU.hdl](./week_02/ALU.hdl)
-  [FullAdder.hdl](./week_02/FullAdder.hdl)
-  [HalfAdder.hdl](./week_02/HalfAdder.hdl)
-  [Inc16.hdl](./week_02/Inc16.hdl)

### Week 03: Flip-Flops and Memory
In this week we learned about how computers remember information with the use of flip-flops, which then form registers and RAMS.

#### Project 03: Memory
-  [Bit.hdl](./week_03/a/Bit.hdl)
-  [PC.hdl](./week_03/a/PC.hdl)
-  [RAM64.hdl](./week_03/a/RAM64.hdl)
-  [RAM8.hdl](./week_03/a/RAM8.hdl)
-  [Register.hdl](./week_03/a/Register.hdl)
-  [RAM16K.hdl](./week_03/b/RAM16K.hdl)
-  [RAM4K.hdl](./week_03/b/RAM4K.hdl)
-  [RAM512.hdl](./week_03/b/RAM512.hdl)

### Week 04: Assembly language
In this week we went up a layer in abstraction and started talking about the Hack Assembly language, a very simple kind of assembly language for a 16 bit platform. The language includes instructions to access a location in memory, load a value to a register, compare two values and jump.

#### Project 04: Multiplication and I/O in Assembly

-   [Mult.asm](./week_04/mult/Mult.asm)
-   [Fill.asm](./week_04/fill/Fill.asm)

### Week 05: CPU
This was the last week working on the hardware platform for the Hack Computer. We learned about many computer architectures (Harvard, Von Neumann) and implented our own creating a fully functional machine.

#### Project 05: CPU

-  [Computer.hdl](./week_05/Computer.hdl)
-  [CPU.hdl](./week_05/CPU.hdl)
-  [Memory.hdl](./week_05/Memory.hdl)

### Week 06: Assembler
With our machine completely finished, we took a look at essential programs for modern software: Assemblers and went on to build our own implementation.

#### Project 06: Assembler
- [Assembler](./week_06/)


### Week 07: Virtual Machines I
In this week we were introduced to the concept of a Virtual Machine (VM) for a high level language. We learned how abstractions like the stack and memory segments work in the assembly level. We then built a VM translator that supports simple instructions, like push, pop, add, sub, gt...

#### Project 07: VM Translator I
-   [VM Translator Source Code](./week_07/)

### Week 08: Virtual Machines II
We finally complete our Virtual Machine by introducing function calls, labels, goto's and if-goto's.

#### Project 08: VM Translator II
-   [VM Translator II Source Code](./week_08/)

### Week 09: High level language
After completing the virtual machine, we were introduced to a high level, object-oriented language called Jack. It's similar to Java and supports most of the features of any modern programming language. We then were asked to build a program with it, and I chose Tetris (since it's the name of the course).

#### Project 09: High Level Language
-   [Tetris](./week_09/Tetris/)

#### Week 10: Compilers I
In this week we looked at the first steps of compilation: tokenization and lexical analysis, and built a simple parser that produces XML code from Jack source files.

#### Project 10: Analyzer 
-   [Analyzer](./week_10/analyzer/)

### Week 11: Compilers II
We finished the Jack Compiler by generating VM code from the Parsing Trees. The result is a compiler for a modern object-oriented language.

#### Project 11: Jack Compiler
-   [Jack Compiler](./week_11/compiler/)

### Week 12: Operating Systems
The final week of the course was reserved for the development of our skills in the construction of an Operating System written in Jack, providing memory allocation, arrays, I/O (Keyboard and Screen), mathematical functions (algorithms for multiplication, division and square roots) and Strings (and string-related functions).

#### Project 12: The JackOS
-   [JackOS](./week_12/)

### Week 13: Final 
In this week we celebrate the construction of fully functional computer, built from Nand to Tetris.
