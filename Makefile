NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT_DIR = utils/libft
LIBFT_NAME = libft.a 
FRAMEWORKS =  -lmlx -framework AppKit -framework OpenGL





SRCS = cub3d.c parsing/parsing.c parsing/parsing_utils.c
OBJS	= $(SRC:.c=.o)

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

pull_master :
	git pull origin master

pull_dev :
	git pull origin master

clean: 
	@rm  -rf  $(OBJS) 
	@make fclean -C $(LIBFT_DIR)/

fclean: clean 
	@rm -rf $(NAME)
	
re : fclean all
# rah makncompiliwch b les flag 