NAME = cub3d

SRC_DIR = src/
BUILD_DIR = build/

# make with asan rule to compile with the adress sanitizer -> make re to get rid of it
ifdef WITH_ASAN
	FLAGS = -Wall -Wextra -Werror -g -fsanitize=address
else
	FLAGS = -Wall -Wextra -Werror
endif

# Includes

INC = inc/
MLX_INC = lib/libmlx42/include/MLX42/

# Libs

LIB = lib/

MLX_DIR = $(LIB)libmlx42
LIBMLX = $(MLX_DIR)/libmlx42.a

LIBFT_DIR = $(LIB)libft
LIBFT = $(LIBFT_DIR)/libft.a

GNL_DIR = $(LIB)gnl/
GNL_UNPREF_SRC = get_next_line.c get_next_line_utils.c
GNL_SRC = $(addprefix $(GNL_DIR), $(GNL_UNPREF_SRC));
GNL_OBJ = $(addprefix $(BUILD_DIR), $(GNL_UNPREF_SRC:.c=.o))

OBJ += $(GNL_OBJ)

# SRC

UNPREFIXED_SRC = main.c \
raycast.c \
line.c \
vector.c \
vector2.c \
player.c \
color.c \
render2d.c \
render.c \

SRC = $(addprefix $(SRC_DIR), $(UNPREFIXED_SRC))

OBJ += $(addprefix $(BUILD_DIR), $(UNPREFIXED_SRC:.c=.o))

# Parse

PARSE_DIR = $(SRC_DIR)parse/

UNPREF_PARSE_SRC = parse.c exit_strerr.c get_textures.c make_texture.c \
get_map.c set_map_content.c flood_fill_map.c

PARSE_SRC = $(addprefix $(PARSE_DIR), $(UNPREF_PARSE_SRC:.=.o))

PARSE_OBJ = $(addprefix $(BUILD_DIR), $(UNPREF_PARSE_SRC:.c=.o))

OBJ += $(PARSE_OBJ)

RESET		=	"\033[0m"
YELLOW		=	"\033[0;33m"