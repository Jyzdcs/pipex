NAME = pipex
CC = gcc
# CFLAGS = -Wall -Wextra -Werror

# Paths to libraries
LIBFT_DIR = ../include/libft
LIBFT = $(LIBFT_DIR)/libft.a
PRINTF_DIR = ../include/Printf
PRINTF = $(PRINTF_DIR)/libftprintf.a

# Source files and object files
SRC = main.c utils.c pipex.c redirections.c parsing.c
OBJ = $(SRC:.c=.o)

# Include paths for header files
INCLUDES = -I$(LIBFT_DIR) -I$(PRINTF_DIR)

all: $(NAME)

# Rule to build the libft library
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Rule to build the printf library
$(PRINTF):
	$(MAKE) -C $(PRINTF_DIR)

# Dependency rules for object files
%.o: %.c pipex.h
	$(CC) $(INCLUDES) -c $< -o $@

# Build the final executable, depends on objects and libraries
$(NAME): $(LIBFT) $(PRINTF) $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LIBFT) $(PRINTF)

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(PRINTF_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(PRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
