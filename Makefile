SRC = src/main.c src/utils.c src/raycasting.c src/parsing/parsing.c\
		src/parsing/map.c
OBJ = src/main.o src/utils.o src/raycasting.o src/parsing/parsing.o\
		src/parsing/map.o
MLX_FLAGS = -Linclude/minilibx-linux -lmlx -L/usr/lib -Iinclude/minilibx-linux -lXext -lX11 -lm -lz
LIBFT_LIB = include/libft/libft.a
LIBFT_DIR = include/libft
GNL_LIB = include/gnl/gnl.a
GNL_DIR = include/gnl
MLX_LIB = include/minilibx-linux
CC = cc 
C_FLAGS = -Wall -Werror -Wextra -g
NAME = cub3d

all : $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJ) $(LIBFT_LIB) $(GNL_LIB)
	make -C $(MLX_LIB)
	$(CC) $(OBJ) $(LIBFT_LIB) $(GNL_LIB) $(MLX_FLAGS) $(C_FLAGS) -o $(NAME)

$(LIBFT_LIB) : $(LIBFT_DIR)
	make -C $(LIBFT_DIR)

$(GNL_LIB) : $(GNL_DIR)
	make -C $(GNL_DIR)

clean:
	make clean -C $(LIBFT_DIR)
	make clean -C $(GNL_DIR)
	rm -rf $(OBJ)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	make fclean -C $(GNL_DIR)
	rm -rf $(NAME)

re: fclean all