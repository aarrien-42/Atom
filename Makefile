# PROGRAM
EXECUTABLE := atom

# FOLDERS
SRC_DIR := src
OBJ_DIR := obj
ASM_DIR := asm
BIN_DIR := bin

# FILES
SOURCES := $(shell find $(SRC_DIR) -name '*.cpp')
HEADERS := $(shell find $(SRC_DIR) -name '*.hpp')
OBJECTS := $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# INCLUDES
SUB_DIR := $(shell find $(SRC_DIR) -type d)
INC_FLAGS := $(addprefix -I, $(SUB_DIR))

# ASSEMBLY
SRC_ASM = code

# COMPILATION
CC = g++
CFLAGS = #-Wall -Wextra -Werror -g3 -fsanitize=address
RM = rm -rf

# COLORS
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;31m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

# RULES
RULES = all run asm clean fclean re

.SILENT:

all: $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(BIN_DIR)/$(EXECUTABLE) $(filter-out $(RULES) ,$(MAKECMDGOALS))
%:
	@:

$(EXECUTABLE) : $(OBJECTS)
	mkdir -p $(BIN_DIR)
	$(CC) $(OBJECTS) -o $(BIN_DIR)/$(EXECUTABLE)
	echo "$(YELLOW)Program compiled!$(DEF_COLOR)"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	printf "$(BLUE)Compiling: $< $(DEF_COLOR)"
	$(CC) $(CFLAGS) $(INC_FLAGS) -o $@ -c $<
	echo "$(GREEN)OK$(DEF_COLOR)"

asm:
	mkdir -p $(BIN_DIR)
	nasm -f elf64 $(ASM_DIR)/$(SRC_ASM).asm -o $(ASM_DIR)/$(SRC_ASM).o
	ld $(ASM_DIR)/$(SRC_ASM).o -o $(BIN_DIR)/$(EXECUTABLE)
	rm $(ASM_DIR)/$(SRC_ASM).o

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(BIN_DIR)

re: fclean all

.PHONY: $(RULES)