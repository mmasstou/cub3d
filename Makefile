NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror  
LIBFT_NAME = libft.a
FRAMEWORKS =  -lmlx -framework AppKit -framework OpenGL

# directions : 
PARS_DIR = parsing/
LIBFT_DIR = utils/libft
# Srcs
SRCS = cub3d.c  _error.c checkargs.c
PARS_SRCS = $(PARS_DIR)parsing.c $(PARS_DIR)stock_minimap.c $(PARS_DIR)is_player.c $(PARS_DIR)check_minimap.c $(PARS_DIR)get_map_size.c  $(PARS_DIR)chech_direction.c $(PARS_DIR)get_g_map.c $(PARS_DIR)parsing_minimap.c
# Objs
OBJS	= $(SRC:.c=.o)
PARS_OBJS	= $(PARS_SRCS:.c=.o)
# All Files 
FILES =  $(SRCS) $(PARS_SRCS)  $(LIBFT_DIR)/$(LIBFT_NAME)

%.o:%.c  
	@${CC} $(CFLAGS)  -I . -o $@ -c $<
	@printf "\x1b[36m   +>\033[0m compiling \033[38;5;42m$< \033[0m\n"

all: $(NAME)

_libft :
	@make bonus -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(PARS_OBJS)  _libft
	@$(CC) $(CFLAGS) $(FILES) -o $(NAME) -g $(FRAMEWORKS)
	@echo "\x1b[36m   +> cub3D \033[0m\033[38;5;42m [Done] \033[0m";

push:fclean
	@git status
	@read -p "Files To Add:" files; git add "$$files" 
	@ read -p "Message:" message; \
	git commit -m "$$message"; \
	git push origin master

clean: 
	@rm  -rf  $(OBJS)  $(PARS_OBJS)
	@make fclean -C $(LIBFT_DIR)/

fclean: clean 
	@rm -rf $(NAME)
	
re : fclean all

# -fsanitize=address