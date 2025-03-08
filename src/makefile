NAME = pipex
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Paths to libraries
LIBFT_DIR = ../include/libft
LIBFT = $(LIBFT_DIR)/libft.a
PRINTF_DIR = ../include/Printf
PRINTF = $(PRINTF_DIR)/libftprintf.a

# Source files and object files
SRC_DIR = .
CMD_DIR = cmd
PARSING_DIR = parsing
PROCESS_DIR = process
REDIR_DIR = redirections
UTILS_DIR = utils

# Source files
SRC = $(SRC_DIR)/main.c \
	$(CMD_DIR)/command.c \
	$(PARSING_DIR)/parsing.c \
	$(PARSING_DIR)/path.c \
	$(PARSING_DIR)/absolute_path.c \
	$(PROCESS_DIR)/process.c \
	$(REDIR_DIR)/redirections.c \
	$(UTILS_DIR)/utils.c

# Object files
OBJ = $(SRC:.c=.o)

# Include paths for header files
INCLUDES = -I$(LIBFT_DIR) -I$(PRINTF_DIR) -I$(SRC_DIR)

all: $(NAME)

# Rule to build the libft library
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Rule to build the printf library
$(PRINTF):
	$(MAKE) -C $(PRINTF_DIR)

# Dependency rules for object files
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

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
