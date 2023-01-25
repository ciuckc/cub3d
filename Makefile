include make_var.mk

all: $(LIBFT) $(LIBMLX) $(NAME)
	
$(LIBFT):
	$(MAKE) -C $(LIB)libft

$(LIBMLX): $(MLX_DIR)
	$(MAKE) -C $(MLX_DIR)

#Exec build

$(NAME): $(OBJ)
	@printf $(YELLOW)"%-33.33s\r"$(RESET) $@
	@$(CC) $(FLAGS) $(OBJ) $(LIBMLX) $(LIBFT) -I$(INC) -I$(MLX_INC) -lm -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -o $(NAME)

#Object build

$(BUILD_DIR)%.o: $(SRC_DIR)%.c | $(BUILD_DIR) $(BUILD_SUBDIRS)
	@printf $(YELLOW)"%-33.33s\r"$(RESET) $@
	@$(CC) $(FLAGS) -I$(INC) -I$(MLX_INC) -c $< -o $@

$(BUILD_DIR)%.o: $(GNL_DIR)%.c | $(BUILD_DIR)
	@printf $(YELLOW)"%-33.33s\r"$(RESET) $@
	@$(CC) $(FLAGS) -I$(INC) -I$(MLX_INC) -c $< -o $@

#Dir dependencies

$(BUILD_DIR):
	@mkdir -p $@

$(BUILD_SUBDIRS):
	@mkdir -p $@

$(MLX_DIR):
	git submodule init
	git submodule update

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
