NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR) -Iminilibx-linux -g
MLX_PATH = minilibx-linux/
MLX_FLAGS = -L$(MLX_PATH) -lmlx -lXext -lX11 -lm

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = includes

SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/raycasting.c \
       $(SRC_DIR)/render.c \
       $(SRC_DIR)/texture.c \
       $(SRC_DIR)/movement.c \
       $(SRC_DIR)/utils.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: make_mlx $(NAME)

make_mlx:
	@make -C $(MLX_PATH)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(MLX_FLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	make -C $(MLX_PATH) clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re make_mlx