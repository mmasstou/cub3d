/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellakr <abellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 20:43:43 by abellakr          #+#    #+#             */
/*   Updated: 2022/08/30 19:08:23 by abellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//-------------------------------------- includes
# include <libc.h>
# include <stdbool.h>
# include "../Resources/libft/libft.h"
# include "../Resources/minilibx_opengl/mlx.h"
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
# define W 1080
# define H 720
# define WALL_STRIPE_WITH 1
# define FOV  60
# define NBR_RAYS W / WALL_STRIPE_WITH 
# define FOV_INC  degreeto_radian(FOV) / NBR_RAYS
# define WALL  7220224
# define EMPTY_SPACE 4511276
# define PLAYER  4539460
# define X__COLOR  0, 96, 255  
# define FOV_COLOR  253, 175, 3
# define WHITE 	16777215
# define GREEN	4511276
# define BLUE	11699
# define PURPLE	13051057
# define BORDER 10
# define RADIUS 80
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

typedef struct s_pos{
	float x;
	float y;
}	t_pos; 
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
	int mm;
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
	// minimap circle
	int	color_circle;
	int	centre;
	float k_x;
	float k_y;
	float x_translation;
	float y_translation;
	float unit_x;
	float unit_y;
	float x1_map;
	float y1_map;
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
//---------------------------------------- mohamed changes
void	my_mlx_pixel_put(int x, int y, t_data *data, int color);
int	close_cross(void *param);
void    render_player(t_data *data, float x, float y, int color);
void	init_player(t_data *data);
void    draw_rect(float x, float y, t_data *data, int color, int type);
int ft_rgb(int t, int r, int g, int b);
void    draw_ceilling_floor(t_data *data);
void	player_update(t_data **data);
double degreeto_radian(float angle);
int	wall_collaction(float index, float jndex, t_data *data);
int ray_caste(t_data *data);
int	draw__map(t_data	*data);
void	draw__player(t_data *data);
int	kay_press(int key, t_data *data);
int	kay_releass(int key, t_data *data);
void	draw__(t_data *data);
int looop__hooking(t_data *data);
void	draw__fov(t_data *data);
void	draw__pov(t_data *data);
void    dda_function(t_data *vars);
//--------------------------------new by bellakrim
void	draw_all(t_data *data);
void 	DrawCircle(int r, t_data *data);
void    dda_circle(double x1, double y1,double x2, double y2,t_data *vars);
void	translation_map(t_data *data);
void	translation_player(t_data *data);
#endif
