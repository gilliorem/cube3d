NAME		= cub3D

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g3 -Imlx

INC_DIR		= inc
SRC_DIR		= src
OBJ_DIR		= obj

ROOT_DIR	= .
LIBFT_DIR	= $(ROOT_DIR)/libft
GNL_DIR		= $(ROOT_DIR)/get_next_line
MLX_DIR		= $(ROOT_DIR)/mlx
#MLX_DIR		= $(ROOT_DIR)/minilibx-linux

INCLUDES	= -I $(INC_DIR) -I $(LIBFT_DIR) -I $(GNL_DIR) -I $(MLX_DIR)

LIBFT		= $(LIBFT_DIR)/libft.a
MLX			= $(MLX_DIR)/libmlx.a
GNL			= $(GNL_DIR)/gnl.a

LIBS		= -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz $(GNL)
#LIBS		= -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit $(GNL)

SRCS		= $(SRC_DIR)/main.c \
			  $(SRC_DIR)/parser.c \
			  $(SRC_DIR)/parser_classify.c \
			  $(SRC_DIR)/parser_check_color.c \
			  $(SRC_DIR)/parser_check_map.c \
			  $(SRC_DIR)/parser_error.c \
			  $(SRC_DIR)/parser_extract_texture.c \
			  $(SRC_DIR)/parser_file.c \
			  $(SRC_DIR)/parser_free.c \
			  $(SRC_DIR)/parser_free_color.c \
			  $(SRC_DIR)/parser_get_color.c \
			  $(SRC_DIR)/parser_get_colors.c \
			  $(SRC_DIR)/parser_get_map.c \
			  $(SRC_DIR)/parser_id.c \
			  $(SRC_DIR)/parser_init.c \
			  $(SRC_DIR)/parser_player_enclose.c \
			  $(SRC_DIR)/parser_process_texture.c \
			  $(SRC_DIR)/parser_scene.c \
			  $(SRC_DIR)/parser_utils.c \
			  $(SRC_DIR)/init_mlx.c \
			  $(SRC_DIR)/textures.c \
			  $(SRC_DIR)/init_ray.c \
			  $(SRC_DIR)/raycaster.c \
			  $(SRC_DIR)/render_wall.c \
			  $(SRC_DIR)/render.c \
			  $(SRC_DIR)/hooks.c \
			  $(SRC_DIR)/hooks_mouse.c \
			  $(SRC_DIR)/minimap.c \
			  $(SRC_DIR)/movement.c \
			  $(SRC_DIR)/player_rotation.c
OBJS		= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(GNL) $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

$(GNL):
	$(MAKE) -C $(GNL_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
