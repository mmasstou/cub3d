/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellakr <abellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 18:35:04 by mmasstou          #+#    #+#             */
/*   Updated: 2022/09/11 15:21:50 by abellakr         ###   ########.fr       */
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
# define ZERO '0'
# define ONE '1'
# define SPACE ' '
// mlx
# define MN 2
# define W 1300
# define H 700
# define WALL_STRIPE_WITH 1
# define WALL  7220224
# define EMPTY_SPACE  13882833
# define PLAYER  4539460
# define HORIZO_TYPE 1
# define VERTIC_TYPE 2
# define FACTO 1
# define TEX_NO 1215
# define TEX_EA 1216
# define TEX_SO 1217
# define TEX_WE 1218
# define WHITE 	16777215
# define GREEN	4511276
# define BLUE	11699
# define BLACK	0
# define PURPLE	13051057
# define BORDER 10
# define RADIUS 120

typedef struct exist
{
	int	no;
	int	so;
	int	we;
	int	ea;
	int	f;
	int	c;
}	t_exist;

typedef struct s_pos{
	double	x;
	double	y;
	int i;
	int j;
}	t_pos;

typedef struct mlx
{
	void	*mlx_ptr;
	void	*mlx_window;
	void	*mlx_image;
	char	*buffer;
	int		bpp;
	int		line_lenght;
	int		endian;
}	t_mlx;

typedef struct s_rays
{
	t_pos			player;
	t_pos			wall_hit;
	t_pos			vertical_wall_hit;
	t_pos			horizontal_wall_hit;
	double			angle;
	double			wall_strip_height;
	double			distance;
	bool			found_horizontal_wall;
	bool			found_vertical_wall;
	bool			was_hit_vertical;
	bool			was_hit_horizontal;
	struct s_rays	*next;
}	t_rays;

typedef struct color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_tex
{
	int				type;
	int				*buff;
	int				width;
	int				height;
	struct s_tex	*next;
}	t_texture;

typedef struct s_player
{
	t_pos		walk_direction;
	t_pos		pos;
	int			y_start_point;
	bool		is_facing_down;
	bool		is_facing_up;
	bool		is_facing_right;
	bool		is_facing_left;
	char		orientation;
	int			turn_direction;
	double		fov;
	double		fov_inc;
	double		rotation_angle;
	double		move_speed;
	double		rotation_speed;
	int			color;
}	t_player;

typedef struct data
{
	t_mlx		*mlx_vars;
	t_player	*player;
	t_rays		*rays;
	t_texture	*tex;
	t_exist		exit;
	t_color		f;
	t_color		c;
	int			params;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		**map;
	int			start_map;
	int			unit;
	int			nbr_rays;
	bool		pressed;
	int			color_circle;
	double		centre;
	int			init_x_mouse;
	double		unit_x;
	double		unit_y;
	double		x_translation;
	double		y_translation;
	double		k_x;
	double		k_y;
	double		x1;
	double		y1;
	double		x2;
	double		y2;
	double		x_fov;
	double		y_fov;

}	t_data;
typedef struct s_line
{
	int	dx;
	int	dy;
	int	e1;
	int	sx;
	int	sy;
	int	e2;
}	t_line;
// -&- SRCS -&-
void		_error(char *msg);
void		checkargs(int argc, char *argv[]);
//----------------------------- Parsing
void		parsing(char *argv[], t_data *data);
void		stock_minimap(char **map, t_data **data, int map_size);
bool		is_player(char c, t_data *data);
void		check_minimap(char **minimap, t_data *data);
int			get_map_size(char *file);
void		chech_direction(char **map, int index, int jndex);
char		**get_g_map(char *file);
void		parsing_minimap(char **g_map, t_data *data);
void		get_map_parameters(char **map, t_data *data);
void		get_line_parameters(char **line, t_data *data);
void		free_array(char **array);
int			array_size(char **tab);
void		save_data(char **line, t_data *data);
void		save_no(char **line, t_data *data);
void		save_so(char **line, t_data *data);
void		save_we(char **line, t_data *data);
void		save_ea(char **line, t_data *data);
void		save_f(char **line, t_data *data);
void		save_c(char **line, t_data *data);
void		save_color(char *color, char *color_data, t_data *data);
void		check_color_validity(char **color_tab);
void		check_color_digit(char **color_tab);
void		free_params(t_data *data);
void		check_files(char *filename);
void		ft_check(t_data *data);
//---------------------------------------- new by bellakrim
void		my_mlx_pixel_put(int x, int y, t_data *data, int color);
int			close_cross(t_data *param);
void		re_draw(t_data *data);
void		init_player(t_player **p);
int			ft_rgb(int t, int r, int g, int b);
void		draw_ceilling_floor(t_data *data);
void		player_update(t_data **data);
double		degreeto_radian(float angle);
int			wall_collaction(float index, float jndex, t_data *data);
int			kay_press(int key, t_data *data);
int			kay_releass(int key, t_data *data);
void		graphic(t_data *data);
void		re_draw__(t_data *data);
int			looop__hooking(t_data *data);
int			ray_caste(t_data *data);
t_rays		*cating_rays(t_data *data, double angle);
double		distance_between_points(double x, double y, double angle);
t_rays		*init_ray(t_data *data, double angle);
t_pos		find_intercept(t_data *data, t_rays *ray, int type);
t_pos		find_horizontal_step(t_data *data, t_rays *ray);
t_pos		find_vertical_step(t_data *data, t_rays *ray);
void		find_horizontal_hit_point(\
			t_data *data, t_rays *ray, t_pos intercept, t_pos step);
void		find_vertical_hit_point(\
			t_data *data, t_rays *ray, t_pos intercept, t_pos step);
t_pos		get_init_distance(t_rays *ray);
void		get_final_distance(t_rays *ray, t_pos distance);
void		normalize_angle(double *angle);
void		rendering_wall(t_data *data, t_rays *rays, int col_id);
void		*ft_reassign(void *oldptr, void *newptr);
void		init_textures(t_data *data);
int			get_texture_color(t_rays *ray, t_data *data, int y);
t_texture	*get_texture(t_texture *tex, t_rays *ray);
void		free_texture(t_texture *tex);
//------------------------- bonus
void		draw_all(t_data *data);
double		percent_function(double value, double max_value);
int			shadowing_function(int color, double percent);
int			mouse_move(int x, int y, void *param);
int			mouse_press(int button, int x, int y, void *param);
int			mouse_release(int button, int x, int y, void *param);
//--------------- draw
void		DrawCircle(int r, t_data *data);
int			draw__map(t_data *data);
void		translation_map(t_data *data);
void		draw__fov(t_data *data);
void		translation_fov(t_data *data, float x, float y);
void		translation_player(t_data *data);
//-----------------
void		dda_circle(t_pos p1, t_pos p2,t_data *vars);
void		draw_rect(double x, double y, t_data *data, int color);
void		draw_line(t_data *data, t_pos p1, t_pos p2);
#endif
