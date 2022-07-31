NAME = cub3D
CC = cc
SRCS = cub3d.c checkargs.c cub_error.c stockData.c
CFLAGS = -Wall -Wextra -Werror
OBJS	= $(SRC:.c=.o)
LIBFT_DIR = utils/libft
LIBFT_NAME = libft.a 
FRAMEWORKS =  utils/minilibx_macos/libmlx.a -framework AppKit -framework OpenGL

%.o:%.c  
	@${CC} $(CFLAGS)  -I . -o $@ -c $<
	@printf "\x1b[36m $@ from {$<}\033[0m\n"

all: $(NAME)

_libft :
	@make bonus -C $(LIBFT_DIR)

$(NAME): $(OBJS) _libft
	@$(CC) $(SRCS) $(LIBFT_DIR)/$(LIBFT_NAME) -o $(NAME) -g $(FRAMEWORKS)
	@echo "\x1b[36m   +> cub3D \033[0m\033[38;5;42m [Done] \033[0m";

push:fclean
	@git status
	@read -p "Files To Add:" files; git add "$$files" 
	@ read -p "Message:" message; \
	git commit -m "$$message"; \
	git push origin master

pull :
	git pull origin master

clean: 
	@rm  -rf  $(OBJS) 
	@make fclean -C $(LIBFT_DIR)/

fclean: clean 
	@rm -rf $(NAME)
	
re : fclean all
