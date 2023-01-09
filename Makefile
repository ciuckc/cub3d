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

ifdef WITH_ASAN
	FLAGS = -Wall -Wextra -Werror -g -fsanitize=address
else
	FLAGS = -Wall -Wextra -Werror
endif

LIB = lib/

MLX_DIR = $(LIB)libmlx42
LIBMLX = $(MLX_DIR)/libmlx42.a

LIBFT_DIR = $(LIB)libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(LIBMLX) $(NAME)
	
$(LIBFT):
	$(MAKE) -C $(LIB)libft

$(MLX_DIR):
	git submodule init
	git submodule update

$(LIBMLX): $(MLX_DIR)
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(LIBMLX) $(LIBFT) -I$(INC) -I$(MLX_INC) -lm -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -o $(NAME)

$(BUILD_DIR)%.o: $(SRC_DIR)%.c | $(BUILD_DIR)
	$(CC) $(FLAGS) -I$(INC) -I$(MLX_INC) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJ)
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MLX_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)
	rm -f $(LIBMLX)

asan: fclean
	$(MAKE) WITH_ASAN=1

re: fclean all

.PHONY:
	all clean fclean re asan
