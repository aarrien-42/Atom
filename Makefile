# PROGRAM
NAME = atom

# FOLDERS
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = inc
ASM_DIR = asm
BIN_DIR = bin

# FILES
SRC = $(wildcard $(SRC_DIR)/*cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
SRC_ASM = code

# COMPILATION
CC = g++
CFLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=address
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

all: $(NAME)

run: $(NAME)
	./$(BIN_DIR)/$(NAME) $(filter-out $(RULES) ,$(MAKECMDGOALS))
%:
	@:

$(NAME) : $(OBJ)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJ) -I $(INC_DIR) -o $(BIN_DIR)/$(NAME)
	echo "$(YELLOW)Program compiled!$(DEF_COLOR)"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	printf "$(BLUE)Compiling: $< $(DEF_COLOR)"
	$(CC) $(CFLAGS) -o $@ -c $< -I $(INC_DIR)
	echo "$(GREEN)OK$(DEF_COLOR)"

asm:
	mkdir -p $(BIN_DIR)
	nasm -f elf64 $(ASM_DIR)/$(SRC_ASM).asm -o $(ASM_DIR)/$(SRC_ASM).o
	ld $(ASM_DIR)/$(SRC_ASM).o -o $(BIN_DIR)/$(NAME)
	rm $(ASM_DIR)/$(SRC_ASM).o

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(BIN_DIR)

re: fclean all

.PHONY: $(RULES)