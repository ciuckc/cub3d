NAME = cub3d

SRC_DIR = src/
BUILD_DIR = build/

UNPREFIXED_SRC = main.c \
parse.c \
raycast.c \
line.c \
vector.c \
vector2.c \
player.c \
color.c \
render2d.c \
render.c \
get_next_line.c \
get_next_line_utils.c

OBJ = $(addprefix $(BUILD_DIR), $(UNPREFIXED_SRC:.c=.o))
SRC = $(addprefix $(SRC_DIR), $(UNPREFIXED_SRC))

INC = inc/
MLX_INC = lib/libmlx42/include/MLX42/

FLAGS = -Wall -Wextra -Werror
#FLAGS = -g -fsanitize=address

LIB = lib/
LIBMLX = lib/libmlx42/libmlx42.a
LIBFT = lib/libft/libft.a

all: $(LIBFT) $(LIBMLX) $(NAME)
	
$(LIBFT):
	$(MAKE) -C $(LIB)libft

$(LIBMLX):
	$(MAKE) -C $(LIB)mlx

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(LIBMLX) $(LIBFT) -I$(INC) -I$(MLX_INC) -lm -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -o $(NAME)

$(BUILD_DIR)%.o: $(SRC_DIR)%.c | $(BUILD_DIR)
	$(CC) $(FLAGS) -I$(INC) -I$(MLX_INC) -c $< -o $@

$(BUILD_DIR):
	mkdir $@

clean:
	rm -f $(OBJ)
	rm -f $(LIB)libft/*.o

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)

re: fclean all

.PHONY:
	all clean fclean re
