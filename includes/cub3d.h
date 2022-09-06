/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 18:35:04 by mmasstou          #+#    #+#             */
/*   Updated: 2022/09/02 18:25:09 by mmasstou         ###   ########.fr       */
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
# define MN 2
# define W 2600 / MN
# define H 1400 / MN
# define WALL_STRIPE_WITH 1
# define FOV  60 * (M_PI / 180)
# define DISTANCE_OF_VIEW 200
# define NBR_RAYS (W / WALL_STRIPE_WITH)
# define FOV_INC  (FOV / NBR_RAYS)
# define WALL  7220224
# define EMPTY_SPACE  13882833
# define PLAYER  4539460
# define X__COLOR  0, 96, 255  
# define FOV_COLOR  253, 175, 3
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
}	t_mlx;

typedef struct rays
{
	double	angle;
	double	wall_strip_height;
	t_position	player;
	t_position	wall_hit;
	t_position	vertical_wall_hit;
	t_position	horizontal_wall_hit;
	bool	found_horizontal_wall;
	bool	found_vertical_wall;
	double	distance;
	bool	wasHitVertical;
	bool	wasHithorizontal;
	bool	hit;
	struct rays *next;
}	t_rays;

typedef struct color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_texture
{
	int		type;
	int		*buff;
	int		width;
	int		height;
	int 	bits_per_pixel;
	int 	size_line;
	int 	endian;
	struct s_texture	*next;
}	t_texture;

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
	t_position  map_coords;
	t_position win_unit;
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

	t_mlx		*mlx_vars;
	t_player	*ply;
	t_rays		*rays;
	t_texture	*tex;
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
	int	color_circle;
	double	centre;
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
void    render_player(t_data *data, float x, float y, int color);

int	move_player_release(int key, t_data *data);
int	move_player_press(int key, t_data *data);
void	re_draw(t_data *data);
int	dda(float x, float y, t_data *data);
int	draw_rays(t_data *data);

int	drawing_minimap(t_data	*data);
void	init_player(t_player **p);
int	drawing_player(t_data	*data);
void    draw_rect(float x, float y, t_data *data, int color);
int	row_dda(float x, float y, float next_x, float next_y, t_data *data);
int	row_ddaa(float x, float y, float next_x, float next_y, t_data *data);
void    updata_data(t_data **data);
int ft_rgb(int t, int r, int g, int b);
void    draw_ceilling_floor(t_data *data);


void    draw_ply(float x, float y, t_data *data, int color);
void	player_render(t_data *data);
void	player_update(t_data **data);
double degreeto_radian(float angle);
void draw_line(t_data *data, int x, int y, int x1, int y1);
void   field_of_views(float x1, float y1, double ray_angle, t_data *data);
int	wall_collaction(float index, float jndex, t_data *data);
int ray_caste(t_data *data);
void    dda_function(t_data *vars);


// 
int	draw__map(t_data	*data);
void	draw__player(t_data *data);
int	kay_press(int key, t_data *data);
int	kay_releass(int key, t_data *data);
void	draw__(t_data *data);
int looop__hooking(t_data *data);
void	draw__fov(t_data *data);
void	draw__pov(t_data *data);
void normalize_angle(double *angle);
void	rendering_wall(t_data *data, t_rays *rays);
void	rendering_walll(t_data *data, t_rays *rays, int col_id);
int mouse_move(int x, int y, t_data *param);
int mouse_move_clik(int x, int y, t_data *param);
void	*ft_reassign(void *oldptr, void *newptr);

// 
void init_textures(t_data *data);
int get_texture_color(t_rays *ray, t_data *data, int y, int wall_strip_height);
void DrawCircle(int r, t_data *data);
void plotCircle(int xm, int ym, int r, t_data *data);
#endif
