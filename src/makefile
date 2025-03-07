NAME = pipex
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Paths to libraries
LIBFT_DIR = ../include/libft
LIBFT = $(LIBFT_DIR)/libft.a
PRINTF_DIR = ../include/Printf
PRINTF = $(PRINTF_DIR)/libftprintf.a

# Source files
SRC = main.c \
	pipe_manager.c process_manager.c \
	error_handler.c validation.c \
	cmd_parser.c path_parser.c \
	file_handler.c redirection.c

# Object files
OBJ = $(SRC:.c=.o)

# Include paths
INCLUDES = -I$(LIBFT_DIR) -I$(PRINTF_DIR)

all: $(NAME)

# Build libraries
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(PRINTF):
	$(MAKE) -C $(PRINTF_DIR)

# Build object files
%.o: %.c pipex.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Build executable
$(NAME): $(LIBFT) $(PRINTF) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT) $(PRINTF)

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
