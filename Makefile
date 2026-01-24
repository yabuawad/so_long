CC      = cc
CFLAGS  = -Wall -Werror -Wextra -I./minilibx-linux

NAME    = so_long

SRC     = get_next_line.c \
          get_next_line_utils.c \
          main.c \
          map_parse1.c \
          map_parse2.c \
          check.c \
          draw.c \
          helper.c\
          check2.c

OBJ     = $(SRC:.c=.o)

MLX_LIB = -L./minilibx-linux -lmlx -lXext -lX11 -lm -lz

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLX_LIB) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re