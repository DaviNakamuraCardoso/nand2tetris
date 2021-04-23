# (S)ource, (L)ibraries and (I)ncludes
S = ./translator/src/
L = ./translator/obj/
I = ./translator/include/

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
dcc: $(L)writer.o $(L)parser.o $(L)dcc.o
	gcc $(L)writer.o $(L)parser.o $(L)dcc.o -o dcc
