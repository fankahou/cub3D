SRC = main.c \
	parse.c \
	parse_line.c \
	parse_check.c \
	init.c \
	error.c \
	utils_array.c \
	utils_free.c

OBJ = $(SRC:.c=.o)

NAME = cub3D

LIBFT = libft/libft.a

MLX_FLAGS = -lmlx -lXext -lX11

CC = cc

CFLAGS = -Wall -Werror -Wextra -g

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(MLX_FLAGS)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -c

$(LIBFT):
	$(MAKE) -C ./libft

clean:
	rm -f $(OBJ)
	$(MAKE) -C ./libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re