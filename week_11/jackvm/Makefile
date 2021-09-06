
# Compiler and flags
CC = gcc
FLAGS = -Wall -Werror

OBJECTS = main.o tokenizer.o ascii.o hash.o tokens.o

# Recipes
%.o: %.c
	$(CC) $(FLAGS) -c $^ -o $@	

all: $(OBJECTS)
	$(CC) $(FLAGS) $^ -o jackvm

clean: 
	rm *.o
