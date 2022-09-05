NAME = cub3D
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBFT_NAME = libft.a

# directions : 
SOURCE = source/
RESOURCE = Resources/
INCLUDES = includes/

PARS_DIR = $(SOURCE)parsing/
LIBFT_DIR = $(RESOURCE)libft
MINILIBX_DIR = $(RESOURCE)minilibx_opengl/


MINIMAP = minimap/
FOV_RAYS = Fov_Rays/
EVENTS = events/

FRAMEWORKS =  $(MINILIBX_DIR)/libmlx.a -framework AppKit -framework OpenGL
# Srcs
SRCS = $(SOURCE)main.c  $(SOURCE)_error.c $(SOURCE)checkargs.c  $(SOURCE)player.c $(SOURCE)Hooks_and_Events.c $(SOURCE)map.c $(SOURCE)ray_cating.c $(SOURCE)render_wall.c $(SOURCE)ft_reassign.c $(SOURCE)draw_ceilling_floor.c $(SOURCE)draw_line.c $(SOURCE)draw__fov.c $(SOURCE)wall_texture.c $(SOURCE)draw_cirle.c
PARS_SRCS = $(PARS_DIR)parsing.c $(PARS_DIR)stock_minimap.c $(PARS_DIR)is_player.c $(PARS_DIR)check_minimap.c $(PARS_DIR)get_map_size.c  $(PARS_DIR)chech_direction.c $(PARS_DIR)get_g_map.c $(PARS_DIR)parsing_minimap.c $(PARS_DIR)parsing_utils.c  $(PARS_DIR)parsing_params.c $(PARS_DIR)save_params.c  $(PARS_DIR)save_params2.c 


# Objs
OBJS	= $(SRCS:.c=.o)
PARS_OBJS	= $(PARS_SRCS:.c=.o)

# All Files 
FILES =  $(SRCS) $(PARS_SRCS)   $(LIBFT_DIR)/$(LIBFT_NAME)  

%.o:%.c
	@${CC} $(CFLAGS) -o $@ -c $<
	@printf "\x1b[36m   +>\033[0m compiling \033[38;5;42m$< \033[0m\n"

all: $(NAME)

_libft :
	@make bonus -C $(LIBFT_DIR)
	@make -C $(MINILIBX_DIR)

$(NAME): $(OBJS) $(PARS_OBJS)  _libft
	@$(CC) $(CFLAGS) $(FRAMEWORKS) $(FILES) -o $(NAME) -g 
	@echo "\x1b[36m   +> cub3D \033[0m\033[38;5;42m [Done] \033[0m";

push:fclean
	@git status
	@read -p "Files To Add:" files; git add "$$files" 
	@ read -p "Message:" message; \
	git commit -m "$$message"; \
	git push

clean: 
	@rm  -rf  $(OBJS)  $(PARS_OBJS)
	@make fclean -C $(LIBFT_DIR)/

fclean: clean 
	@rm -rf $(NAME) cub3D.dSYM
	
re : fclean all

# -fsanitize=address
# SANIT = -static-libsan -fsanitize=address
