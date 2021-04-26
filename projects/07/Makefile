# (S)ource, (L)ibraries and (I)ncludes
S = ./translator/src/
L = ./translator/obj/
I = ./translator/include/


# Tree module
$(L)tree.o: $(S)tree.c
	gcc -I$(I) -c $(S)tree.c -o $(L)tree.o

# Commands module
$(L)commands.o: $(S)commands.c
	gcc -I$(I) -c $(S)commands.c -o $(L)commands.o

# Parser module
$(L)parser.o: $(S)parser.c
	gcc -I$(I) -c $(S)parser.c -o $(L)parser.o

# Writer module
$(L)writer.o: $(S)writer.c
	gcc -I$(I) -c $(S)writer.c -o $(L)writer.o

# Main module
$(L)dcc.o: $(S)dcc.c
	gcc -I$(I) -c $(S)dcc.c -o $(L)dcc.o

# Executable
dcc: $(L)tree.o $(L)commands.o $(L)writer.o $(L)parser.o $(L)dcc.o
	gcc $(L)tree.o $(L)commands.o $(L)writer.o $(L)parser.o $(L)dcc.o -o dcc
