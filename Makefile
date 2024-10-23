SRC = src/main.c src/utils.c
OBJ = src/main.o src/utils.o
MLX_FLAGS = -Linclude/minilibx-linux -lmlx -L/usr/lib -Iinclude/minilibx-linux -lXext -lX11 -lm -lz
LIBFT_LIB = include/libft/libft.a
LIBFT_DIR = include/libft
CC = cc 
C_FLAGS = -Wall -Werror -Wextra -g
NAME = cub3d

all : $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJ) $(LIBFT_LIB)
	$(CC) $(OBJ) $(LIBFT_LIB) $(MLX_FLAGS) $(C_FLAGS) -o $(NAME)

$(LIBFT_LIB) : $(LIBFT_DIR)
	make -C $(LIBFT_DIR)

clean:
	make clean -C $(LIBFT_DIR)
	rm -rf $(OBJ)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -rf $(NAME)

re: fclean all