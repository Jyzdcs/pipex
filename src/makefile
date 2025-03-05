NAME = pipex
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC = main.c utils.c pipex.c redirections.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
