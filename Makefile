SRC_DIR = ./src/
SRC = src/main.c src/utils.c src/raycasting.c src/init.c src/move_player.c\
		src/draw.c src/rotate.c src/parsing/parsing.c src/parsing/color.c\
		src/frees.c src/parsing/map.c src/parsing/texture.c\
		src/parsing/map_walls.c
OBJ = $(SRC:.c=.o)
MLX_FLAGS = -Linclude/minilibx-linux -lmlx -L/usr/lib -Iinclude/minilibx-linux -lXext -lX11 -lm -lz
LIBFT_LIB = include/libft/libft.a
LIBFT_DIR = include/libft
GNL_LIB = include/gnl/gnl.a
GNL_DIR = include/gnl
MLX_LIB = include/minilibx-linux
BONUS_DIR = ./bonus/
BONUS_SRC = bonus/minimap.c bonus/main_bonus.c src/utils.c src/raycasting.c\
		src/init.c src/move_player.c src/draw.c src/rotate.c src/frees.c\
		src/parsing/parsing.c src/parsing/map.c src/parsing/texture.c\
		src/parsing/color.c src/parsing/map_walls.c bonus/gun.c
BONUS_OBJ = $(BONUS_SRC:.c=.o)
CC = cc
C_FLAGS = -Wall -Werror -Wextra -g
NAME = cub3d
NAME_BONUS = cub3d_bonus

all : $(NAME)

$(SRC_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(C_FLAGS) -c $< -o $@

$(NAME) : $(OBJ) $(LIBFT_LIB) $(GNL_LIB)
	make -C $(MLX_LIB)
	$(CC) $(C_FLAGS) $(OBJ) $(LIBFT_LIB) $(GNL_LIB) $(MLX_FLAGS)  -o $(NAME)

$(LIBFT_LIB) : $(LIBFT_DIR)
	make -C $(LIBFT_DIR)

$(GNL_LIB) : $(GNL_DIR)
	make -C $(GNL_DIR)

$(BONUS_DIR)%.o: $(BONUS_DIR)%.c
	$(CC) $(C_FLAGS) -c $< -o $@

$(NAME_BONUS) : $(BONUS_OBJ) $(LIBFT_LIB) $(GNL_LIB)
	$(CC) $(C_FLAGS) $(BONUS_OBJ) $(LIBFT_LIB) $(GNL_LIB) $(MLX_FLAGS)  -o $(NAME_BONUS)

bonus: $(NAME_BONUS)

clean:
	make clean -C $(LIBFT_DIR)
	make clean -C $(GNL_DIR)
	rm -rf $(OBJ) $(BONUS_OBJ)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	make fclean -C $(GNL_DIR)
	rm -rf $(NAME) $(NAME_BONUS)

re: fclean all