NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror
#-I$(INC_DIR) -Iminilibx-linux -g
#MLX_PATH = minilibx-linux/
MLX_FLAGS = -lmlx -lXext -lX11 -lm #-L$(MLX_PATH) 
LIBFT = libft/libft.a

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = includes

SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/raycasting.c \
	   $(SRC_DIR)/raycasting_calculate.c \
       $(SRC_DIR)/render.c \
	   $(SRC_DIR)/render_draw.c \
       $(SRC_DIR)/texture.c \
       $(SRC_DIR)/movement.c \
	   $(SRC_DIR)/movement_wasd.c \
       $(SRC_DIR)/utils.c \
	   $(SRC_DIR)/utils_texture.c \
	$(SRC_DIR)/parse.c \
	$(SRC_DIR)/parse_line.c \
	$(SRC_DIR)/parse_check.c \
	$(SRC_DIR)/init.c \
	$(SRC_DIR)/error.c \
	$(SRC_DIR)/utils_array.c \
	$(SRC_DIR)/utils_free.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME) #make_mlx

#make_mlx:
#	@make -C $(MLX_PATH)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(MLX_FLAGS) $(LIBFT) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C ./libft

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C ./libft clean
# make -C $(MLX_PATH) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re make_mlx