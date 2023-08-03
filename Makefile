# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude -g

# Source files
SRCS = src/so_long.c src/map_validation.c src/map_wall_validation.c src/map_path.c \
       getnextline/get_next_line.c src/error.c src/map_mlx.c getnextline/get_next_line_utils.c \
	   src/map_init.c

# Object files
OBJS = $(SRCS:.c=.o)

# Libraries
LIBS = -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
LIBFT = ./libft/libft.a
LIBPRINTF = ./printf/libftprintf.a
LIBMLX42 = ./MLX42/build/libmlx42.a

# Executable
EXECUTABLE = so_long

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS) $(LIBFT) $(LIBPRINTF) $(LIBMLX42)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBPRINTF) $(LIBMLX42) $(LIBS) -o $(EXECUTABLE)

$(LIBFT):
	$(MAKE) -C libft

$(LIBPRINTF):
	$(MAKE) -C printf

$(LIBMLX42):
	$(MAKE) -C MLX42/build

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C libft clean
	$(MAKE) -C printf clean
	$(MAKE) -C MLX42/build clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C libft fclean
	$(MAKE) -C printf fclean
	$(MAKE) -C MLX42/build fclean
	rm -f $(EXECUTABLE)

re: fclean all

.PHONY: all clean fclean re
