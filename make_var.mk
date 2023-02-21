NAME = cub3D

SRC_DIR = src/
BUILD_DIR = build/
BUILD_SUBDIRS = build/draw_util build/gameplay build/parse build/render build/render2d build/vector build/sprites

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
render/raycast.c \
render/render.c \
render/draw_line.c \
render/set_pixel_color.c \
vector/vector.c \
vector/vector2.c \
gameplay/player.c \
gameplay/enemy.c \
draw_util/color.c \
draw_util/get_pixel.c \
render2d/init.c \
render2d/minimap.c \
parse/exit_strerr.c \
parse/flood_fill_map.c \
parse/get_map.c \
parse/get_textures.c \
parse/make_texture.c \
parse/set_map_content.c \
parse/crop_map.c \
parse/fill_from_pos.c \
parse/init_tile_map.c \
parse/add_neighbours_to_queue.c \
parse/get_map_range.c \
parse/reach_neighbours.c \
parse/parse.c \
sprites/sprite_display.c \
sprites/sprite_util.c \
sprites/collec_util.c \
sprites/sprite_sort.c \

SRC = $(addprefix $(SRC_DIR), $(UNPREFIXED_SRC))

OBJ += $(addprefix $(BUILD_DIR), $(UNPREFIXED_SRC:.c=.o))

RESET		=	"\033[0m"
YELLOW		=	"\033[0;33m"
