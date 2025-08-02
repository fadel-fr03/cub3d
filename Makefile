NAME			= cub3D
BONUS_NAME		= cub3D_bonus

# Compiler and flags
CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g
INCLUDES		= -I./includes -I./libft -I./minilibx-linux

# Directories
SRC_DIR			= ./src
OBJ_DIR			= ./obj
BONUS_OBJ_DIR	= ./obj_bonus
LIBFT_DIR		= ./libft
MLX_DIR			= ./minilibx-linux

# Libraries
LIBFT			= $(LIBFT_DIR)/libft.a
MLX				= $(MLX_DIR)/libmlx.a
LIBS			= -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# Source files
SRCS = $(SRC_DIR)/main.c \
		$(SRC_DIR)/parsing/parse_file.c \
		$(SRC_DIR)/parsing/parse_file2.c \
		$(SRC_DIR)/parsing/parse_file3.c \
		$(SRC_DIR)/parsing/parse_file4.c \
		$(SRC_DIR)/parsing/parse_textures.c \
		$(SRC_DIR)/parsing/parse_textures2.c \
		$(SRC_DIR)/parsing/parse_textures3.c \
		$(SRC_DIR)/parsing/parse_map.c \
		$(SRC_DIR)/parsing/validate_map.c \
		$(SRC_DIR)/parsing/validate_map2.c \
		$(SRC_DIR)/parsing/validate_map3.c \
		$(SRC_DIR)/graphics/init_mlx.c \
		$(SRC_DIR)/graphics/init_player_dir.c \
		$(SRC_DIR)/raycasting/raycaster.c \
		$(SRC_DIR)/raycasting/render_walls.c \
		$(SRC_DIR)/raycasting/draw_vertical_line.c \
		$(SRC_DIR)/events/keyboard.c \
		$(SRC_DIR)/events/keyboard2.c \
		$(SRC_DIR)/utils/errors.c \
		$(SRC_DIR)/utils/clean_game.c \
		$(SRC_DIR)/utils/cleanup.c \
		$(SRC_DIR)/utils/get_next_line_utils.c \
		$(SRC_DIR)/utils/get_next_line.c \
		$(SRC_DIR)/utils/map_utils.c

BONUS_SRCS = $(SRC_DIR)/bonus/minimap.c \
			 $(SRC_DIR)/bonus/minimap2.c \
			 $(SRC_DIR)/bonus/mouse.c

# Object files
OBJS			= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
BONUS_MAIN_OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BONUS_OBJ_DIR)/%.o)
BONUS_OBJS		= $(BONUS_SRCS:$(SRC_DIR)/%.c=$(BONUS_OBJ_DIR)/%.o)

# Color codes
GREEN	= \033[0;32m
YELLOW	= \033[0;33m
RED		= \033[0;31m
NC		= \033[0m

# Default rule
all: $(LIBFT) $(MLX) $(NAME)

$(NAME): $(OBJS)
	@echo "$(RED)Removing $(BONUS_NAME) if it exists...$(NC)"
	@rm -f $(BONUS_NAME)
	@echo "$(YELLOW)Linking $(NAME)...$(NC)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)$(NAME) created successfully!$(NC)"

# Compile normal object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compile bonus object files (with -DBONUS)
$(BONUS_OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)[BONUS] Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) -DBONUS $(INCLUDES) -c $< -o $@

# Build libft
$(LIBFT):
	@echo "$(YELLOW)Building libft...$(NC)"
	@make -C $(LIBFT_DIR) --no-print-directory
	@echo "$(GREEN)libft built successfully!$(NC)"

# Build minilibx
$(MLX):
	@echo "$(YELLOW)Building minilibx...$(NC)"
	@make -C $(MLX_DIR) --no-print-directory
	@echo "$(GREEN)minilibx built successfully!$(NC)"

# Bonus target - standard Make behavior (only rebuilds if needed)
$(BONUS_NAME): $(LIBFT) $(MLX) $(BONUS_MAIN_OBJS) $(BONUS_OBJS)
	@echo "$(RED)Removing default binary ($(NAME)) if exists...$(NC)"
	@rm -f $(NAME)
	@echo "$(YELLOW)Linking $(BONUS_NAME)...$(NC)"
	@$(CC) $(CFLAGS) $(BONUS_MAIN_OBJS) $(BONUS_OBJS) $(LIBS) -o $(BONUS_NAME)
	@echo "$(GREEN)$(BONUS_NAME) created successfully!$(NC)"

# Phony wrapper for convenience
bonus: $(BONUS_NAME)

# Clean object files
clean:
	@echo "$(RED)Cleaning object files...$(NC)"
	@rm -rf $(OBJ_DIR) $(BONUS_OBJ_DIR)
	@make -C $(LIBFT_DIR) clean --no-print-directory
	@make -C $(MLX_DIR) clean --no-print-directory

# Clean all
fclean: clean
	@echo "$(RED)Removing binaries...$(NC)"
	@rm -f $(NAME) $(BONUS_NAME)
	@make -C $(LIBFT_DIR) fclean --no-print-directory

# Rebuild
re: fclean all

# Phony targets
.PHONY: all clean fclean re bonus