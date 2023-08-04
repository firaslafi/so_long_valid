# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flafi <flafi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/04 20:40:25 by flafi             #+#    #+#              #
#    Updated: 2023/08/04 23:41:58 by flafi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
CC = cc
AR = ar rcs
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror -g
GLFW_FLAGS = -ldl -lglfw -L /Users/$(USER)/.brew/Cellar/glfw/3.3.8/lib
LIBFT_PATH = ./libft/libft.a
MLX_PATH = MLX42/build/libmlx42.a
PRINT_PATH = printf/libftprintf.a
SRC = src/so_long.c src/map_validation.c src/map_wall_validation.c src/map_path.c \
      getnextline/get_next_line.c src/error.c src/map_mlx.c getnextline/get_next_line_utils.c \
      src/map_init.c
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
OBJ_DIR = obj

all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(MLX_PATH) $(LIBFT_PATH) $(PRINT_PATH) $(OBJ)
	@$(CC) $(OBJ) -o $(NAME) $(LIBFT_PATH) $(MLX_PATH) $(PRINT_PATH) $(CFLAGS) $(GLFW_FLAGS)
	@echo "\033[31m ------------------***༺ (\033[31m\033[32mSo_long Compiled!\033[31m)༻***------------------\n\033[0m"

$(MLX_PATH):
	@cd ./MLX42 && cmake -S . -B build && cmake --build build -j4
	@echo "\033[31m ------------------***༺ (\033[31m\033[32mMLX Generated!\033[31m)༻***------------------\n\033[0m"
	clear
.SILENT:
$(LIBFT_PATH):
	@make -C ./libft --silent

$(PRINT_PATH):
	@make -C ./printf --silent
clean:
	@$(RM) $(OBJ_DIR)
	@make -C ./libft clean --silent
	@make -C ./printf clean --silent
	@make -C ./MLX42/build clean --silent
	rm -f  ./src/*.o ./src/*.out --silent
	rm -f  ./getnextline/*.o ./getnextline/*.out --silent
	@echo "\033[31m ------------------***༺ (\033[31m\033[32mCleaned!\033[31m)༻***------------------\n\033[0m"

fclean: clean
	@$(RM) $(NAME)
	@make -C ./libft fclean --silent
	@make -C ./printf fclean --silent
	@echo "\033[31m ------------------***༺ (\033[31m\033[32mExecutable Removed!\033[31m)༻***------------------\n\033[0m"

re: fclean all

.PHONY: all clean fclean re
