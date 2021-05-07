# Makefile

# (L)ibraries, (S)ource, (O)bjects, (I)ncludes
L = ./lib/
S = ./src/
O = ./obj/
I = ./include/

# (T)okenizer and (C)ompilation engine
T = tokenizer/
C = compengine/

# Precompilation functions
$(O)$(T)precomp.o: $(S)$(T)precomp.c
	gcc -I$(I) -c $(S)$(T)precomp.c -o $(O)$(T)precomp.o

# Tokens
$(O)$(T)tokens.o: $(S)$(T)tokens.c
	gcc -I$(I) -c $(S)$(T)tokens.c -o $(O)$(T)tokens.o

# Reader
$(O)$(T)reader.o: $(S)$(T)reader.c
	gcc -I$(I) -c $(S)$(T)reader.c -o $(O)$(T)reader.o

# Cleaner
$(O)$(T)cleaner.o: $(S)$(T)cleaner.c
	gcc -I$(I) -c $(S)$(T)cleaner.c -o $(O)$(T)cleaner.o

# Tokenizer library
$(L)libtokenizer.a: $(O)$(T)tokens.o
	ar -rcs $(L)libtokenizer.a $(O)$(T)tokens.o

# Main module
$(O)dcc.o: $(S)dcc.c
	gcc -I$(I) -c $(S)dcc.c -o $(O)dcc.o

# Executable
dcc: $(O)dcc.o $(L)libtokenizer.a
	gcc -I$(I) -L$(L) $(O)dcc.o -ltokenizer -o dcc
