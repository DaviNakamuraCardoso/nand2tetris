# Makefile for the test suite of the Davi Compiler Collection


# (S)ource, (L)ibraries, (O)bjects, (H)eaders
S = ./src/
L = ./lib/
O = ./obj/
H = ./includes/

# (T)okenizer and (C)ompilation engine
T = tokenizer/
C = compengine/

# (TH) Test Header, ()
TH = ./../include/
TS = ./../src/
TL = ./../lib/
TO = ./../obj/

CH = ./../include/
CS = ./../src/

# Test the creation of tokens
$(O)$(T)test_tokens.o: $(S)$(T)test_tokens.c
	gcc -I$(TH) -c $(S)$(T)test_tokens.c -o $(O)$(T)test_tokens.o

# Get the tokenizer module
$(O)$(T)tokens_test.o: $(TS)$(T)tokens.c
	gcc -I$(TH) -c $(TS)$(T)tokens.c -o $(O)$(T)tokens_test.o

# Test the precomp
$(O)$(T)test_precomp.o: $(S)$(T)test_precomp.c
	gcc -I$(TH) -c $(S)$(T)test_precomp.c -o $(O)$(T)test_precomp.o

# Get the precomp module
$(O)$(T)precomp_test.o: $(TS)$(T)precomp.c
	gcc -I$(TH) -c $(TS)$(T)precomp.c -o $(O)$(T)precomp_test.o

# Test the precomp
$(O)$(T)test_cleaner.o: $(S)$(T)test_cleaner.c
	gcc -I$(TH) -c $(S)$(T)test_cleaner.c -o $(O)$(T)test_cleaner.o

# Test the reader
$(O)$(T)test_reader.o: $(S)$(T)test_reader.c
	gcc -I$(TH) -c $(S)$(T)test_reader.c -o $(O)$(T)test_reader.o

# Get the reader module
$(O)$(T)test_module_reader.o: $(TS)$(T)reader.c
	gcc -I$(TH) -c $(TS)$(T)reader.c -o $(O)$(T)test_module_reader.o

# Get the precomp module
$(O)$(T)cleaner_test.o: $(TS)$(T)cleaner.c
	gcc -I$(TH) -c $(TS)$(T)cleaner.c -o $(O)$(T)cleaner_test.o

# Test the parser
$(O)$(T)test_parser.o: $(S)$(T)test_parser.c
	gcc -I$(TH) -c $(S)$(T)test_parser.c -o $(O)$(T)test_parser.o

# Get the parser module
$(O)$(T)test_module_parser.o: $(TS)$(T)parser.c
	gcc -I$(TH) -c $(TS)$(T)parser.c -o $(O)$(T)test_module_parser.o

# Test the parser
$(O)$(C)test_parser.o: $(S)$(C)test_parser.c
	gcc -I$(TH) -c $(S)$(C)test_parser.c -o $(O)$(C)test_parser.o

# Get the parser module
$(O)$(C)test_module_parser.o: $(CS)$(C)parser.c
	gcc -I$(TH) -c $(CS)$(C)parser.c -o $(O)$(C)test_module_parser.o

# Tokenizer test
$(L)libtesttokenizer.a: $(O)$(T)test_tokens.o $(O)$(T)tokens_test.o $(O)$(T)test_precomp.o $(O)$(T)precomp_test.o $(O)$(T)test_cleaner.o $(O)$(T)cleaner_test.o $(O)$(T)test_reader.o $(O)$(T)test_module_reader.o $(O)$(T)test_parser.o $(O)$(T)test_module_parser.o
	ar -rcs $(L)libtesttokenizer.a $(O)$(T)test_tokens.o $(O)$(T)tokens_test.o $(O)$(T)test_precomp.o $(O)$(T)precomp_test.o $(O)$(T)test_cleaner.o $(O)$(T)cleaner_test.o $(O)$(T)test_reader.o $(O)$(T)test_module_reader.o $(O)$(T)test_parser.o $(O)$(T)test_module_parser.o


$(L)libtestcompengine.a: $(O)$(C)test_parser.o $(O)$(C)test_module_parser.o
	ar -rcs $(L)libtestcompengine.a $(O)$(C)test_parser.o $(O)$(C)test_module_parser.o


# Main test file
$(O)tests.o: $(S)tests.c
	gcc -I$(H) -c $(S)tests.c -o $(O)tests.o

# Executable
tests: $(O)tests.o $(L)libtesttokenizer.a $(L)libtestcompengine.a
	gcc -I$(TH) -L$(L) $(O)tests.o  -ltesttokenizer -ltestcompengine -o tests
