NAME = cube
TITLE = cube

LIBFT_PATH = libft
LIBFT = $(LIBFT_PATH)/libft.a
LIBFT_FLAGS = -L$(LIBFT_PATH) -lft

FT_PRINTF_PATH = $(LIBFT_PATH)/ft_printf
FT_PRINTF_LIB = $(FT_PRINTF_PATH)/libftprintf.a

CC = cc
CFLAGS = -Wall -Werror -Wextra -I$(LIBFT_PATH) -Iincludes -g -gdwarf-4
RM = rm -rf

OBJS_DIR = objs
SRCS_DIR = srcs

SRC = srcs/main.c

OBJ = $(SRC:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBFT_FLAGS)
	@printf "\033[0;32m$(TITLE) compiled OK!\n"
	@printf "CUBE3D compiled!\n"
	@printf "\033[0;37m"

# Object file compilation (silent)
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

bonus: all

# Compile Libft and ft_printf (silent)
$(LIBFT): $(FT_PRINTF_LIB)
	@$(MAKE) -C $(LIBFT_PATH) --no-print-directory > /dev/null

$(FT_PRINTF_LIB):
	@$(MAKE) -C $(FT_PRINTF_PATH) --no-print-directory > /dev/null

clean:
	@$(RM) $(OBJ)
	@$(RM) $(OBJS_DIR)
	@$(MAKE) -C $(LIBFT_PATH) clean --no-print-directory > /dev/null
	@$(MAKE) -C $(FT_PRINTF_PATH) clean --no-print-directory > /dev/null
	@printf "\033[0;31m$(TITLE) cleaned!\n"
	@printf "\033[0;37m"

fclean:
	@$(RM) $(OBJ)
	@$(RM) $(OBJS_DIR)
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean --no-print-directory > /dev/null
	@$(MAKE) -C $(FT_PRINTF_PATH) fclean --no-print-directory > /dev/null
	@printf "\033[0;31m$(TITLE) removed!\n"
	@printf "\033[0;37m"

re: fclean all

run: $(NAME)
	@clear
	@./$(NAME)

valgrind: $(NAME)
	@valgrind --leak-check=full --show-leak-kinds=all --suppressions=supp.supp ./$(NAME)

.PHONY: all clean fclean re bonus run valgrind 

