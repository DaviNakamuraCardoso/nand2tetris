# Makefile for the test suite of the Davi Compiler Collection


# (S)ource, (L)ibraries, (O)bjects, (H)eaders
S = ./src/
L = ./lib/
O = ./obj/
H = ./includes/

# (T)okenizer and (C)ompilation engine
T = tokenizer/
C = compengine/
U = utils/

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

# Test the statements
$(O)$(C)test_statements.o: $(S)$(C)test_statements.c
	gcc -I$(CH) -c $(S)$(C)test_statements.c -o $(O)$(C)test_statements.o

# Get the statements module
$(O)$(C)test_module_statements.o: $(CS)$(C)statements.c
	gcc -I$(CH) -c $(CS)$(C)statements.c -o $(O)$(C)test_module_statements.o

# Test the compile
$(O)$(C)test_compile.o: $(S)$(C)test_compile.c
	gcc -I$(CH) -c $(S)$(C)test_compile.c -o $(O)$(C)test_compile.o

# Get the compile module
$(O)$(C)test_module_compile.o: $(CS)$(C)compile.c
	gcc -I$(CH) -c $(CS)$(C)compile.c -o $(O)$(C)test_module_compile.o


# Test the expressions
$(O)$(C)test_expressions.o: $(S)$(C)test_expressions.c
	gcc -I$(CH) -c $(S)$(C)test_expressions.c -o $(O)$(C)test_expressions.o

# Get the expressions module
$(O)$(C)test_module_expressions.o: $(CS)$(C)expressions.c
	gcc -I$(CH) -c $(CS)$(C)expressions.c -o $(O)$(C)test_module_expressions.o


# Test the structure
$(O)$(C)test_structure.o: $(S)$(C)test_structure.c
	gcc -I$(CH) -c $(S)$(C)test_structure.c -o $(O)$(C)test_structure.o

# Get the structure module
$(O)$(C)test_module_structure.o: $(CS)$(C)structure.c
	gcc -I$(CH) -c $(CS)$(C)structure.c -o $(O)$(C)test_module_structure.o

# Test the analyzer
$(O)$(C)test_analyzer.o: $(S)$(C)test_analyzer.c
	gcc -I$(CH) -c $(S)$(C)test_analyzer.c -o $(O)$(C)test_analyzer.o

# Get the analyzer module
$(O)$(C)test_module_analyzer.o: $(CS)$(C)analyzer.c
	gcc -I$(CH) -c $(CS)$(C)analyzer.c -o $(O)$(C)test_module_analyzer.o


$(O)$(U)tests.o: $(CS)$(U)tests.c
	gcc -I$(CH) -c $(CS)$(U)tests.c -o $(O)$(U)tests.o

# Tokenizer test
$(L)libtesttokenizer.a: $(O)$(T)test_tokens.o $(O)$(T)tokens_test.o $(O)$(T)test_precomp.o $(O)$(T)precomp_test.o $(O)$(T)test_cleaner.o $(O)$(T)cleaner_test.o $(O)$(T)test_reader.o $(O)$(T)test_module_reader.o $(O)$(T)test_parser.o $(O)$(T)test_module_parser.o
	ar -rcs $(L)libtesttokenizer.a $(O)$(T)test_tokens.o $(O)$(T)tokens_test.o $(O)$(T)test_precomp.o $(O)$(T)precomp_test.o $(O)$(T)test_cleaner.o $(O)$(T)cleaner_test.o $(O)$(T)test_reader.o $(O)$(T)test_module_reader.o $(O)$(T)test_parser.o $(O)$(T)test_module_parser.o

# Compengine test
$(L)libtestcompengine.a: $(O)$(C)test_parser.o $(O)$(C)test_module_parser.o $(O)$(C)test_statements.o $(O)$(C)test_module_statements.o $(O)$(C)test_compile.o $(O)$(C)test_module_compile.o $(O)$(C)test_expressions.o $(O)$(C)test_module_expressions.o $(O)$(C)test_structure.o $(O)$(C)test_module_structure.o $(O)$(C)test_analyzer.o $(O)$(C)test_module_analyzer.o
	ar -rcs $(L)libtestcompengine.a $(O)$(C)test_parser.o $(O)$(C)test_module_parser.o $(O)$(C)test_statements.o $(O)$(C)test_module_statements.o $(O)$(C)test_compile.o $(O)$(C)test_module_compile.o $(O)$(C)test_expressions.o $(O)$(C)test_module_expressions.o $(O)$(C)test_structure.o $(O)$(C)test_module_structure.o $(O)$(C)test_analyzer.o $(O)$(C)test_module_analyzer.o


$(L)libtestutils.a: $(O)$(U)tests.o
	ar -rcs $(L)libtestutils.a $(O)$(U)tests.o

# Main test file
$(O)tests.o: $(S)tests.c
	gcc -I$(H) -c $(S)tests.c -o $(O)tests.o

# Executable
tests: $(O)tests.o $(L)libtesttokenizer.a $(L)libtestcompengine.a $(L)libtestutils.a
	gcc -I$(TH) -L$(L) $(O)tests.o  -ltesttokenizer -ltestcompengine -ltestutils -o tests
