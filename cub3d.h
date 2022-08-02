#ifndef CUB3D_H
# define CUB3D_H

# include <libc.h>
# include <stdbool.h>
# include "utils/libft/libft.h"

# define COLOR_SUCCESS "\033[38;5;42m"
# define COLOR_FAILURE "\x1b[31m"
# define COLOR_END "\x1b[0m"

# define ZERO '0'
# define ONE '1'
# define SPACE ' '

typedef struct color
{
    int r;
    int g;
    int b;
}   t_color;

typedef struct data
{
    char    *no;
    char    *so;
    char    *we;
    char    *ea;
    t_color f;
    t_color c;
    char  **map;
}   t_data;

enum dir{
    NORD = 121,
    EAST,
    WEST,
    SOUTH
};
// -&- SRCS -&-
void    _error(char *msg);
//----------------------------- Parsing
void    parsing(char *argv[], t_data *data);
void    stock_minimap(char **minimap, t_data **data, int minimap_size);
bool    is_player(char c);
void    check_minimap(char **minimap, t_data *data);
int     get_map_size(char *file);
void    chech_direction(char **map, int index, int jndex);
char    **get_g_map(char *file);
void    print_minimap(char **g_map);
void    parsing_minimap(char **g_map, t_data *data);
#endif