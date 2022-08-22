/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 11:25:05 by mmasstou          #+#    #+#             */
/*   Updated: 2022/08/22 22:05:26 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//-------------------------------------- includes
# include <libc.h>
# include <stdbool.h>
# include "utils/libft/libft.h"
# include "minilibx_opengl/mlx.h"
# include <math.h>
# include "key.h"
//------------------------------------------------ macros
# define COLOR_SUCCESS "\033[38;5;42m"
# define COLOR_FAILURE "\x1b[31m"
# define COLOR_END "\x1b[0m"

# define ZERO '0'
# define ONE '1'
# define SPACE ' '
// mlx
# define W 1200
# define H 720
# define FOV 60
# define FOV_INC  FOV / 120
# define WALL  7220224
# define EMPTY_SPACE  13882833
# define PLAYER  4539460

// claver Key
# define STEP(x, y) (x > y) ? x:y
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

typedef struct s_player{
	char spawning_orientation;
	int color;
	float ply_w;
	float x_pos;
	float y_pos;
	float x_pos_o;
	float y_pos_o;
	int radius;
	int turn_direction; // -1 if left , +1 if right
	int walk_direction; // -1 if back , +1 if front
	double rotation_angle;
	double move_speed;
	double rotation_speed;
}	t_player;
//---------------------------------
typedef struct data
{
	float x1;
	float y1;
	float x2;
	float y2;
	t_mlx	*mlx_vars;
	t_player *ply;
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
	// ++++
	int		h;
	double		zoom;
	float			x_player;
	float			y_player;
	int			last_x;
	int			last_y;
	int unit;
	// player movement
	double		bita;
	int		p_up;
	// rays
	int		nextx;
	int		nexty;
	int		deltax;
	int		deltay;
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
void	draw_rec(int x, int y, t_data *data, int color, int type);
int	esc(int keycode, t_data *data);
int	close_cross(void *param);
void    render_player(float x,float y, t_data *data, int color, int type);

int	move_player_release(int key, t_data *data);
int	move_player_press(int key, t_data *data);
void	re_draw(t_data *data);
int	dda(float x, float y, t_data *data);
int	draw_rays(t_data *data);

int	drawing_minimap(t_data	*data);
t_player	*init_player(t_player **p);
int	drawing_player(t_data	*data);
void    draw_rect(float x, float y, t_data *data, int color, int type);
int	row_dda(float x, float y, float next_x, float next_y, t_data *data);
int	row_ddaa(float x, float y, float next_x, float next_y, t_data *data);
void    updata_data(t_data **data);
int ft_rgb(int t, int r, int g, int b);
void    draw_ceilling_floor(t_data *data);


void    draw_ply(float x, float y, t_data *data, int color);
void	player_render(t_data *data);
void	player_updata(t_data **data);
double degreeto_radian(int angle);
void draw_line(t_data *data, int x, int y, int x1, int y1);
void   field_of_views(float x1, float y1, t_data *data);
int	wall_collaction(float index, float jndex, t_data *data);
int ray_caste(t_data *data);
#endif
