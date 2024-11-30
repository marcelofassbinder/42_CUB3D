GREEN = \e[0;32m
BLUE = \e[1;034m
RED = \e[0;31m
MAGENTA = \033[1;35m
ORANGE = \033[1;38;5;208m
GREY = \033[0;37m
CYAN = \e[1;36m
RESET = \e[0m

LIBFT_LIB = include/libft/libft.a
LIBFT_DIR = include/libft
GNL_LIB = include/gnl/gnl.a
GNL_DIR = include/gnl
MLX_FLAGS = -Linclude/minilibx-linux -lmlx -L/usr/lib -Iinclude/minilibx-linux -lXext -lX11 -lm -lz
MLX_DIR = include/minilibx-linux/
MLX = $(MLX_DIR)libmlx.a
SRC_DIR = ./src/
OBJ_DIR = ./objs/
SRC = main.c utils.c raycasting.c init.c move_player.c\
		draw.c rotate.c parsing/parsing.c parsing/color.c\
		frees.c parsing/map.c parsing/texture.c\
		parsing/map_walls.c image.c
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
BONUS_DIR = ./bonus/
BONUS_SRC = utils.c image.c raycasting.c parsing/color.c draw.c\
		parsing/map_walls.c init.c move_player.c rotate.c\
		frees.c parsing/parsing.c parsing/map.c parsing/texture.c\
		bonus/minimap.c bonus/main_bonus.c bonus/gun.c bonus/door.c\
		bonus/mouse.c
BONUS_OBJ = $(addprefix $(OBJ_DIR), $(BONUS_SRC:.c=.o))
CC = cc
C_FLAGS = -Wall -Werror -Wextra -g
NAME = cub3D
NAME_BONUS = cub3D_bonus

all : $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(C_FLAGS) -c $< -o $@

$(NAME) : $(MLX) $(OBJ) $(LIBFT_LIB) $(GNL_LIB)
	@echo "$(CYAN)[!]$(RESET) Working on project ... "
	@$(CC) $(C_FLAGS) $(OBJ) $(LIBFT_LIB) $(GNL_LIB) $(MLX_FLAGS) -o $(NAME) > /dev/null 2>&1
	@echo "$(GREEN)[✔] CUB3D ready!$(RESET)"

$(LIBFT_LIB) : $(LIBFT_DIR)
	@echo "$(CYAN)[!]$(RESET) Working on LIBFT_LIB ..."
	@make -C $(LIBFT_DIR) > /dev/null 2>&1
	@echo "$(ORANGE)[✔] LIBFT ready!$(RESET)"

$(GNL_LIB) : $(GNL_DIR)
	@echo "$(CYAN)[!]$(RESET) Working on GNL_LIB ..."
	@make -C $(GNL_DIR) > /dev/null 2>&1
	@echo "$(ORANGE)[✔] GNL ready!$(RESET)"

$(MLX): $(MLX_DIR)
	@rm -rf include/minilibx-linux/.git
	@make -C $(MLX_DIR) >/dev/null 2>&1

$(MLX_DIR):
	@echo "$(CYAN)[!]$(RESET) Preparing minilibx ..."
	@cd include && git clone https://github.com/42Paris/minilibx-linux.git > /dev/null 2>&1

$(OBJ_DIR)%.o: $(BONUS_DIR)%.c
	@$(CC) $(C_FLAGS) -c $< -o $@

$(NAME_BONUS) : $(MLX) $(BONUS_OBJ) $(LIBFT_LIB) $(GNL_LIB) 
	@echo "$(CYAN)[!]$(RESET) Working on bonus ... "
	@$(CC) $(C_FLAGS) $(BONUS_OBJ) $(LIBFT_LIB) $(GNL_LIB) $(MLX_FLAGS) -o $(NAME_BONUS) > /dev/null 2>&1
	@echo "$(GREEN)[✔] CUB3D bonus ready!$(RESET)"

bonus: $(NAME_BONUS)

clean:
	@echo "$(CYAN)[!]$(RESET) Executing cleaning ..."
	@make clean -C $(LIBFT_DIR) > /dev/null 2>&1
	@make clean -C $(GNL_DIR) > /dev/null 2>&1
	@rm -rf $(OBJ) $(BONUS_OBJ) > /dev/null 2>&1
	@echo "$(RED)[✔] Cleaned!$(RESET) "

fclean: clean
	@echo "$(CYAN)[!]$(RESET) Executing full cleaning..."
	@make fclean -C $(LIBFT_DIR) > /dev/null 2>&1
	@make fclean -C $(GNL_DIR) > /dev/null 2>&1
	@rm -rf $(NAME) $(NAME_BONUS) $(OBJ_DIR) > /dev/null 2>&1
	@rm -rf $(NAME) $(MLX_DIR)
	@echo "$(RED)[✔] Full cleaning done!$(RESET) "

re: fclean all