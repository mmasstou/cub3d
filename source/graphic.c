/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellakr <abellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 18:11:18 by mmasstou          #+#    #+#             */
/*   Updated: 2022/09/11 11:01:25 by abellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//-------------------------------------------------- graphic
void	graphic(t_data *data)
{
	t_mlx	*mlx;

	data->mlx_vars = (t_mlx *)malloc(sizeof(t_mlx));
	if (!data->mlx_vars)
		_error(NULL);
	mlx = data->mlx_vars;
	mlx->mlx_ptr = mlx_init();
	if (mlx->mlx_ptr == NULL)
		_error("MLX error");
	mlx->mlx_window = mlx_new_window(mlx->mlx_ptr, W, H, "cub3d");
	mlx->mlx_image = mlx_new_image(mlx->mlx_ptr, W, H);
	mlx->buffer = mlx_get_data_addr(\
	mlx->mlx_image, &mlx->bpp, &mlx->line_lenght, &mlx->endian);
	init_textures(data);
	draw_all(data);
	mlx_put_image_to_window(\
	mlx->mlx_ptr, mlx->mlx_window, mlx->mlx_image, 0, 0);
	mlx_hook(mlx->mlx_window, KEYPRESS, 1L << 0, kay_press, data);
	mlx_hook(mlx->mlx_window, KEYRELEASE, 1L << 1, kay_releass, data);
	mlx_hook (mlx->mlx_window, 17, 1L << 0, close_cross, data);
	//---- add function to handle mouse hooks 
	mlx_hook (data->mlx_vars->mlx_window, 4, 1L << 0, mouse_press, data);
	mlx_hook (data->mlx_vars->mlx_window, 5, 1L << 0, mouse_release, data);	
	mlx_hook (data->mlx_vars->mlx_window, 6, 1L << 0, mouse_move, data);
	mlx_loop_hook(mlx->mlx_ptr, looop__hooking, data);
	mlx_loop (mlx->mlx_ptr);
}
//------------------------------------------------ redraw 
void	re_draw__(t_data *data)
{
	t_mlx	*mlx;

	mlx = data->mlx_vars;
	mlx_clear_window(mlx->mlx_ptr, mlx->mlx_window);
	mlx_destroy_image(mlx->mlx_ptr, mlx->mlx_image);
	mlx->mlx_image = mlx_new_image(mlx->mlx_ptr, W, H);
	mlx->buffer = mlx_get_data_addr(\
	mlx->mlx_image, &mlx->bpp, &mlx->line_lenght, &mlx->endian);
	draw_all(data);
	mlx_put_image_to_window(\
	mlx->mlx_ptr, mlx->mlx_window, mlx->mlx_image, 0, 0);
}
//------------------------------------- bonus
void	draw_all(t_data *data)
{
	draw_ceilling_floor(data);
	ray_caste(data);
	DrawCircle(RADIUS, data);
	draw__map(data);
	draw__fov(data);
}
//-----------------------------------------------------
int mouse_move(int x, int y, void *param)
{
	t_data *data = (t_data *)param;
	if(data->pressed == TRUE && x < W && x >= 0 && y < H && y >= 0)
	{
		data->player->rotation_speed = degreeto_radian(2.5);
		if(data->init_x_mouse - x < 0)
			data->player->turn_direction = 1;
		else if(data->init_x_mouse - x > 0)
			data->player->turn_direction = -1;
	}
	return(0);
}
//-----------------------------------------
int mouse_press(int button, int x, int y, void *param)
{
	t_data *data = (t_data *)param;
	if(button == 1 && x < W && x >= 0 && y < H && y >= 0)
	{
		data->pressed = TRUE;
		data->init_x_mouse = x;
	}
	return(0);
}
//----------------------------
int mouse_release(int button, int x, int y, void *param)
{
	t_data *data = (t_data *)param;
	if(button == 1 && x < W && x >= 0 && y < H && y >= 0 )
	{
		data->pressed = FALSE;
		data->player->turn_direction = 0;
	}
	else if(x > W || x < 0 || y > H || y < 0)
	{
		data->pressed = FALSE;
		data->player->turn_direction = 0;
	}
	return(0);
}
//------------------------------------------ draw circle function
void DrawCircle(int r, t_data *data)
{
    double i;
	double angle;
	double x1;
	double  y1;
	
	i = 0;
	data->color_circle = WHITE;
	data->centre = r + BORDER;
	while(i < 360)
	{
        angle = i;
        x1 = r * cos(angle * M_PI / 180) + r;
        y1 = r * sin(angle * M_PI / 180) + r;
        dda_circle(r + BORDER, r + BORDER, x1 + BORDER, y1 + BORDER, data);
		i+=0.01;
    }
}
//----------------- draw line function  for circle
void    dda_circle(double x1, double y1,double x2, double y2,t_data *vars)
{
    double    steps;
    double    dx;
    double    dy;

    dx = x2 - x1;
    dy = y2 - y1;
    if (fabs(dx) > fabs(dy))
        steps = fabs(dx);
    else
        steps = fabs(dy);
    dx /= steps;
    dy /= steps;
    while ((int)(x1 - x2) || (int)(y1 - y2))
    {
        my_mlx_pixel_put(x1 , y1 , vars, vars->color_circle);
        x1 += dx;
        y1 += dy;
    }
}
//--------------------------------------------------------------------------------
void    draw_rect(double x, double y, t_data *data, int color, int type)
{
	int index;
	int jndex;
	int i;
	int j;

	index = (x + data->unit);
	i = (y + data->unit); 
	j = y;
	while (x <= index - type)
	{
		jndex = i;
		y = j;
		while (y <= jndex - type)
		{
            if(sqrt(pow(x - data->centre, 2) + pow(y - data->centre, 2)) < RADIUS)
				my_mlx_pixel_put(x, y, data, color);
			y++;
		}
		x++;
	}
}
//------------------------------------------------------------------------
int	draw__map(t_data *data)
{
	
	int index = 0;
	int jndex;
	data->unit = 30;
	while (data->map[index])
	{
		jndex = 0;
		while (data->map[index][jndex] && data->map[index][jndex] != '\n')
		{
			data->unit_x = jndex * data->unit;
			data->unit_y = index * data->unit;
			translation_map(data);
			if (data->map[index][jndex] == '0' || ft_strchr("SNWE", data->map[index][jndex]) != NULL)
				draw_rect(data->x_translation, data->y_translation, data, EMPTY_SPACE, 0);
			else if (data->map[index][jndex] == '1')
				draw_rect(data->x_translation, data->y_translation, data, WALL, 0);
			jndex ++;
		}
		index ++;
	}
	return (0);
}
//------------------------------------------- translation map
void	translation_map(t_data *data)
{
	data->k_x = data->player->pos.x * data->unit - data->centre;
	data->k_y = data->player->pos.y * data->unit - data->centre;
	//-----------------------------------------
	if(data->k_x == 0)
		data->x_translation = data->unit_x;
	if(data->k_x > 0)
		data->x_translation = data->unit_x - fabs(data->k_x);
	else if(data->k_x < 0)
		data->x_translation = data->unit_x + fabs(data->k_x);
		//----------------------------
	if(data->k_y == 0)
		data->y_translation = data->unit_y;
	else if(data->k_y < 0)
		data->y_translation = data->unit_y + fabs(data->k_y);
	else if(data->k_y > 0)
		data->y_translation = data->unit_y - fabs(data->k_y);
}
//---------------------------------------------------- draw fieald of view 
void	draw__fov(t_data *data)
{
	t_rays *tmp;
	
	tmp = data->rays;
	data->color_circle = 0;
	translation_player(data);
	while(tmp)
	{
		data->x1 = data->x_translation;
		data->y1 = data->y_translation;
		translation_fov(data, tmp->wall_hit.x, tmp->wall_hit.y);
		data->x2 = data->x_fov;
		data->y2 = data->y_fov;
		//color
		data->player->color = BLACK;
		draw_line(data, data->x_translation, data->y_translation, data->x_fov, data->y_fov);
		tmp = tmp->next;
	}
}
//------------------------------------------- translation fov
void translation_fov(t_data *data, float x, float y)
{
	data->k_x = data->player->pos.x * data->unit - data->centre;
	data->k_y = data->player->pos.y * data->unit - data->centre;
	if(data->k_x == 0)
		data->x_fov = x;
	else if(data->k_x > 0)
		data->x_fov = x - fabs(data->k_x);
	else if(data->k_x < 0)
		data->x_fov = x + fabs(data->k_x);
	if(data->k_y == 0)
		data->y_fov = y;
	else if(data->k_y < 0)
		data->y_fov = y + fabs(data->k_y);
	else if(data->k_y > 0)
		data->y_fov = y - fabs(data->k_y);
}
//-------------------------------------------------------------
void	translation_player(t_data *data)
{
	data->k_x = data->player->pos.x * data->unit - data->centre;
	data->k_y = data->player->pos.y * data->unit - data->centre;
	if(data->k_x == 0)
		data->x_translation = data->player->pos.x * data->unit;
	else if(data->k_x > 0)
		data->x_translation = data->player->pos.x * data->unit - fabs(data->k_x);
	else if(data->k_x < 0)
		data->x_translation = data->player->pos.x * data->unit + fabs(data->k_x);
	if(data->k_y == 0)
		data->y_translation = data->player->pos.y * data->unit;
	else if(data->k_y < 0)
		data->y_translation = (data->player->pos.y * data->unit) + fabs(data->k_y);
	else if(data->k_y > 0)
		data->y_translation = (data->player->pos.y * data->unit) - fabs(data->k_y);
}