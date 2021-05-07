

# Test the creation of tokens
$(O)test_tokens.o: $(S)test_tokens.c
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

# Tokenizer test
$(L)libtesttokenizer.a: $(O)$(T)test_tokens.o $(O)$(T)tokens_test.o $(O)$(T)test_precomp.o $(O)$(T)precomp_test.o
	ar -rcs $(L)libtesttokenizer.a $(O)$(T)test_tokens.o $(O)$(T)tokens_test.o $(O)$(T)test_precomp.o $(O)$(T)precomp_test.o
