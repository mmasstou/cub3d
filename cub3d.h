#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "utils/libft/libft.h"
# include "utils/minilibx_macos/mlx.h"

# define COLOR_SUCCESS "\033[38;5;42m"
# define COLOR_FAILURE "\x1b[31m"
# define COLOR_END "\x1b[0m"

# define W 1440
# define H 800
typedef struct color
{
    int r;
    int g;
    int b;
}   t_color;

typedef struct	s_pos
{
	double	x;
	double	y;
}				t_pos;

typedef struct cub3d_data
{
    char    *no;
    char    *so;
    char    *we;
    char    *ea;
    t_color f;
    t_color c;
    t_list  *map;
    int     **m;
}   t_data;

void    checkargs(int argc, char *argv[], t_data *data);
void    cub_error(char *title, char *msg, char *extra_msg);
int     stock_data(char *argv, t_data **data);
#endif