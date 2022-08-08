/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellakr <abellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 11:25:05 by mmasstou          #+#    #+#             */
/*   Updated: 2022/08/08 18:33:51 by abellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//-------------------------------------- includes
# include <libc.h>
# include <stdbool.h>
# include "utils/libft/libft.h"
# include <mlx.h>
//------------------------------------------------ macros
# define COLOR_SUCCESS "\033[38;5;42m"
# define COLOR_FAILURE "\x1b[31m"
# define COLOR_END "\x1b[0m"

# define ZERO '0'
# define ONE '1'
# define SPACE ' '
// mlx
# define W 1970
# define H 1150
//------------------------------------- structs
typedef struct exist
{
    int no;
    int so;
    int we;
    int ea;
    int f;
    int c;
}   t_exist;

//---------------------------- new by bellakrim
typedef struct mlx
{
	void *mlx_ptr;
	void *mlx_window;
	void *mlx_image;
	//------------------------ for image filling
	char	*buffer;
	int		bpp;
	int		line_lenght;
	int		endian;
	//-------------------------
}t_mlx;
//-------------------------------- new by bellakrim
typedef struct color
{
	int	r;
	int	g;
	int	b;
}	t_color;
//---------------------------------
typedef struct data
{
	t_mlx	*mlx_vars;
	int     params;
	t_exist exit;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	p;
	t_color	f;
	t_color	c;
	char	**map;
	int		start_map;
}	t_data;

enum e_dir{
	NORD = 121,
	EAST,
	WEST,
	SOUTH
};

// -&- SRCS -&-
void	_error(char *msg);
void	checkargs(int argc, char *argv[]);
//----------------------------- Parsing
void	parsing(char *argv[], t_data *data);
void	stock_minimap(char **minimap, t_data **data, int minimap_size);
bool	is_player(char c, t_data *data);
void	check_minimap(char **minimap, t_data *data);
int		get_map_size(char *file);
void	chech_direction(char **map, int index, int jndex);
char	**get_g_map(char *file);
void	parsing_minimap(char **g_map, t_data *data);
void    get_map_parameters(char **map, t_data *data);
void    get_line_parameters(char **line, t_data *data);
void    free_array(char **array);
int		array_size(char **tab);
void	save_data(char **line, t_data *data);
void	save_no(char **line, t_data *data);
void	save_so(char **line, t_data *data);
void	save_we(char **line, t_data *data);
void	save_ea(char **line, t_data *data);
void	save_f(char **line, t_data *data);
void	save_c(char **line, t_data *data);
void	save_color(char *color, char *color_data, t_data *data);
void	check_color_validity(char **color_tab);
void	check_color_digit(char **color_tab);
void    free_params(t_data *data);
void	check_files(char *filename);
void    ft_error(void);
void	ft_check(t_data *data);
//---------------------------------------- new by bellakrim
void    graphic(t_data *data);
void	draw_minimap(t_data *data);
void	my_mlx_pixel_put(int x, int y, t_data *data, int color);
void    draw_rec(int x, int y, t_data *data, int color);
#endif
