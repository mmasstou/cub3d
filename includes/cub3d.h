/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellakr <abellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 20:43:43 by abellakr          #+#    #+#             */
/*   Updated: 2022/09/03 21:01:05 by abellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//-------------------------------------- includes
# include <libc.h>
# include <stdbool.h>
# include <stdlib.h>
# include <limits.h>
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
# define W 1870
# define H 970
# define WALL_STRIPE_WITH 1
# define FOV  60  * (M_PI / 180)
# define NBR_RAYS W / WALL_STRIPE_WITH
# define FOV_INC  (FOV / NBR_RAYS)
# define WALL  7220224
# define EMPTY_SPACE 4511276
# define PLAYER  4539460
# define X__COLOR  0, 96, 255  
# define FOV_COLOR  253, 175, 3
# define WHITE 	16777215
# define GREEN	4511276
# define BLUE	11699
# define BLACK	0
# define PURPLE	13051057
# define BORDER 10
# define RADIUS 120
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
	double x;
	double y;
}	t_position; 
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

typedef struct rays
{
	double	angle;
	t_position	wall_hit;
	t_position	vertical_wall_hit;
	t_position	horizontal_wall_hit;
	double	distance;
	bool	wasHitVertical;
	bool	wasHithorizontal;
	struct rays *next;
}	t_rays;

typedef struct color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_player{
	int win_middle_width;
	char spawning_orientation;
	int color;
	float ply_w;
	float x_pos;
	float y_pos;
	float x_pos_o;
	float y_pos_o;
	int radius;
	int turn_direction; // -1 if left , +1 if right
	int turn_direction_mouse; // -1 if left , +1 if right
	int mouse_clik; // -1 if left , +1 if right
	int walk_direction; // -1 if back , +1 if front
	double rotation_angle;
	double move_speed;
	double rotation_speed;
}	t_player;
//---------------------------------
typedef struct data
{
	// ? this vas is to rayCasting 
	t_position	step; // ! calcul ths Delta 
	t_position	intercept;  // ! git first intercept
	t_position	Horizontal_hit; 
	t_position	Vertical_hit;
	bool	was_hit_vertical;
	bool	is_facing_down;
	bool	is_facing_up;
	bool	is_facing_right;
	bool	is_facing_left;
	double horizontal_distance;
	double vertical_distance;
	// ? end
	int mm;
	float x1;
	float y1;
	float x2;
	float y2;
	t_rays *rays;
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
	t_position	map_size;
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
	double	centre;
	double k_x;
	double k_y;
	double x_translation;
	double y_translation;
	double unit_x;
	double unit_y;
	double x1_map;
	double y1_map;
	double x_fov;
	double y_fov;
	//---------------------------mouse data;
	bool pressed;
	int init_x_mouse;
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
void	init_player(t_data *data);
void    draw_rect(double x, double y, t_data *data, int color, int type);
int ft_rgb(int t, int r, int g, int b);
void    draw_ceilling_floor(t_data *data);
void	player_update(t_data **data);
double degreeto_radian(float angle);
int	wall_collaction(float index, float jndex, t_data *data);
int ray_caste(t_data *data);
int	draw__map(t_data	*data);
int	kay_press(int key, t_data *data);
int	kay_releass(int key, t_data *data);
void	draw__(t_data *data);
int looop__hooking(t_data *data);
void	draw__fov(t_data *data);
//--------------------------------new by bellakrim
void	draw_all(t_data *data);
void 	DrawCircle(int r, t_data *data);
void	translation_map(t_data *data);
void	translation_player(t_data *data);
void normalize_angle(double *angle);
void	rendering_wall(t_data *data, t_rays *rays);
void	rendering_walll(t_data *data, t_rays *rays, int col_id);
void	*ft_reassign(void *oldptr, void *newptr);
void translation_fov(t_data *data, float x, float y);
//-----------------------------------------------------------------------------
void 	draw_line(t_data *data, int x, int y, int x1, int y1);
void    dda_circle(double x1, double y1,double x2, double y2,t_data *vars);
void    dda_function(t_data *vars);
//---------------------------------mouse hooks
int mouse_move(int x, int y, void *param);
int mouse_press(int button, int x, int y, void *param);
int mouse_release(int button, int x, int y, void *param);
double	percent_function(double value, double max_value);
int shadowing_function(int color, double percent);
#endif
