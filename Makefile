NAME = cube3d
TITLE = cube3d

LIBFT_PATH = libft
LIBFT = $(LIBFT_PATH)/libft.a
MLX_PATH = mlx
MLX  = $(MLX_PATH)/libmlx.a
LIBFT_FLAGS = -L$(LIBFT_PATH) -lft

CC = gcc
CFLAGS = -Wall -Werror -Wextra -I$(LIBFT_PATH) -Iincludes -g -gdwarf-4
MLX_FLAGS = -Imlx -Lmlx -lmlx -lX11 -lXext -lm

RM = rm -rf

OBJS_DIR = objs
SRCS_DIR = srcs

SRC = srcs/main.c\
      srcs/general_utils/strs_utils.c\
      srcs/map/create_map.c\
      srcs/map/map_utils.c\
      srcs/map/map_checks.c\
      srcs/game/game_loop.c\
      srcs/raycasting/raycasting_setup.c\
			textures/textures.c\

OBJ = $(SRC:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

$(NAME): $(MLX) $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) -o $@ $^ $(MLX_FLAGS) $(LIBFT_FLAGS)  # Order matters here
	@printf "\033[0;32m$(TITLE) compiled OK!\n"
	@printf "CUBE3D compiled!\n"
	@printf "\033[0;37m"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(MLX) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH) --no-print-directory

$(MLX):
	@$(MAKE) -C $(MLX_PATH) --no-print-directory


clean:
	@$(RM) $(OBJ)
	@$(RM) $(OBJS_DIR)
	@$(MAKE) -C $(LIBFT_PATH) clean --no-print-directory > /dev/null
	@printf "\033[0;31m$(TITLE) cleaned!\n"
	@printf "\033[0;37m"

fclean:
	@$(RM) $(OBJ)
	@$(RM) $(OBJS_DIR)
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean --no-print-directory > /dev/null
	@printf "\033[0;31m$(TITLE) removed!\n"
	@printf "\033[0;37m"

re: fclean all

run: $(NAME)
	@clear
	@./$(NAME)

valgrind: $(NAME)
	@valgrind --leak-check=full --show-leak-kinds=all --suppressions=supp.supp ./$(NAME)

.PHONY: all clean fclean re run valgrind

