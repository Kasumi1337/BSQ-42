# SRC DIR
SRC_DIR = srcs

# SRC FILES
SRC_FILES = file_reader.c input_reader.c main.c parse.c solver.c

# SRC
SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

# OBJ DIR
OBJ_DIR = objs

# OBJ FILES
OBJ_FILES = $(SRC_FILES:.c=.o)

# OBJ
OBJ = $(addprefix $(OBJ_DIR)/, $(OBJ_FILES))

# Compiler
CC = gcc

# Flags
CFLAGS = -Wall -Wextra -Werror

# INCLUDE path
INCLUDE = includes/

# Output program
NAME = bsq

# Rule to build the library
all: $(NAME)

# Rule to build the library from the object files
$(NAME): $(OBJ_DIR) $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

# Rule to compile .c files in ./srcs/ into .o files in ./srcs/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $(CFLAGS) -I$(INCLUDE) $< -o $@

# Rule to clean up object files
clean:
	rm -rf $(OBJ_DIR)

# Rule to clean everything (object files + the library)
fclean:	clean
	rm -f $(NAME)

# Rule to rebuild everything
re:	fclean all

# Define MakeFiles usage
.PHONY = all clean fclean re
