# Makefile for the Hack Assemebler Program (hasm)

# (S)ource, (L)ibraries and (I)ncludes
S = ./assembler/source/
L = ./assembler/lib/
I = ./assembler/includes/

$(L)table.o: $(S)table.c
	gcc -I$(I) -c $(S)table.c -o $(L)table.o
$(L)parser.o: $(S)parser.c
	gcc -I$(I) -c $(S)parser.c -o $(L)parser.o
$(L)hasm.o: $(S)hasm.c
	gcc -I$(I) -c $(S)hasm.c -o $(L)hasm.o
hasm: $(L)table.o $(L)parser.o $(L)hasm.o
	gcc $(L)table.o $(L)parser.o $(L)hasm.o -o hasm
