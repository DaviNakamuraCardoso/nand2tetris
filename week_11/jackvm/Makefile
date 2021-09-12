
# Paths
O = ./obj/
S = ./src/
I = ./include/

# Compiler and flags
CC = gcc
FLAGS = -Wall -Wextra 

# Targets
CMDS = push pop operators jumps
CMDSP = $(foreach cmd, $(CMDS), $(addprefix cmds/, $(cmd)))
MODULES = main tokenizer ascii hash tokens list vm $(CMDSP) 
OBJPATHS = $(foreach obj, $(MODULES), $(addprefix $(O), $(obj)))  
OBJECTS = $(foreach obj, $(OBJPATHS), $(addsuffix .o, $(obj)))

# Recipes
$(O)%.o: $(S)%.c
	$(CC) -I $(I) $(FLAGS) -c $^ -o $@	

all: $(OBJECTS)
	$(CC) $(FLAGS) $^ -o jackvm

clean: 
	rm $(O)*.o

test:
	$(CC) tests/test.c -o tests/test
