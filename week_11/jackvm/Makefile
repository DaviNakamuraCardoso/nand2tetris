
# Paths
O = ./obj/
S = ./src/
I = ./include/

# Compiler and flags
CC = gcc
FLAGS = -Wall -Wextra -Werror

# Targets
MODULES = main tokenizer ascii hash tokens list
OBJPATHS = $(foreach obj, $(MODULES), $(addprefix $(O), $(obj)))  
OBJECTS = $(foreach obj, $(OBJPATHS), $(addsuffix .o, $(obj)))

# Recipes
$(O)%.o: $(S)%.c
	$(CC) -I $(I) $(FLAGS) -c $^ -o $@	

all: $(OBJECTS)
	$(CC) $(FLAGS) $^ -o jackvm

clean: 
	rm $(O)*.o
