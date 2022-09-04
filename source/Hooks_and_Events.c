/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Hooks_and_Events.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellakr <abellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 18:35:28 by mmasstou          #+#    #+#             */
/*   Updated: 2022/09/04 18:26:43 by abellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//----------------------------------------------- graphic function
void	draw__(t_data *data){
	data->mlx_vars = (t_mlx *)malloc(sizeof(t_mlx));
    if(!data->mlx_vars)
        ft_error();
    data->mlx_vars->mlx_ptr = mlx_init();
	if (data->mlx_vars->mlx_ptr == NULL)
		_error("MLX error");
    data->mlx_vars->mlx_window = mlx_new_window ( data->mlx_vars->mlx_ptr, W, H,"cub3d");
    data->mlx_vars->mlx_image = mlx_new_image(data->mlx_vars->mlx_ptr, W, H);
    data->mlx_vars->buffer = mlx_get_data_addr (data->mlx_vars->mlx_image, &data->mlx_vars->bpp, &data->mlx_vars->line_lenght, &data->mlx_vars->endian);
	draw_all(data);
    mlx_put_image_to_window (data->mlx_vars->mlx_ptr, data->mlx_vars->mlx_window, data->mlx_vars->mlx_image, 0, 0);
	mlx_hook(data->mlx_vars->mlx_window, KeyPress, KeyPressMask, kay_press, data);
	mlx_hook(data->mlx_vars->mlx_window, KeyRelease, KeyReleaseMask, kay_releass, data);
	mlx_hook (data->mlx_vars->mlx_window, 17, 1L << 0, close_cross, data);
	//---- add function to handle mouse hooks ;
	mlx_hook (data->mlx_vars->mlx_window, 4, 1L << 0, mouse_press, data);
	mlx_hook (data->mlx_vars->mlx_window, 5, 1L << 0, mouse_release, data);	
	mlx_hook (data->mlx_vars->mlx_window, 6, 1L << 0, mouse_move, data);
	mlx_loop_hook(data->mlx_vars->mlx_ptr, looop__hooking, data);
    mlx_loop (data->mlx_vars->mlx_ptr);
}
//----------------------------------------------------------------------------------- redraw function
void	re_draw__(t_data *data){
	mlx_clear_window(data->mlx_vars->mlx_ptr, data->mlx_vars->mlx_window);
	mlx_destroy_image(data->mlx_vars->mlx_ptr,data->mlx_vars->mlx_image);
    data->mlx_vars->mlx_image = mlx_new_image(data->mlx_vars->mlx_ptr, W, H);
    data->mlx_vars->buffer = mlx_get_data_addr (data->mlx_vars->mlx_image, &data->mlx_vars->bpp, &data->mlx_vars->line_lenght, &data->mlx_vars->endian);
	draw_all(data);
    mlx_put_image_to_window (data->mlx_vars->mlx_ptr, data->mlx_vars->mlx_window, data->mlx_vars->mlx_image, 0, 0);
}
//------------------------------------------------------ loop hooking 
int looop__hooking(t_data *data)
{
	player_update(&data);
	re_draw__(data);
	return (0);
}
//----------------------------------------------------- close cross
int	close_cross(void *param)
{
	(void)param;
	exit (0);
}
//----------------------------------------------------------------------
int	kay_press(int key, t_data *data){

	if (key == 53)
	{
		mlx_destroy_image (data->mlx_vars->mlx_ptr, data->mlx_vars->mlx_image);
		mlx_destroy_window (data->mlx_vars->mlx_ptr, data->mlx_vars->mlx_window);
		exit (0);
	}
	else if (key == S_KEY)
		data->ply->walk_direction = -1;
	else if (key == W_KEY)
		data->ply->walk_direction = 1;
	else if (key == AROW_LEFT)
	{
		data->ply->rotation_speed = degreeto_radian(3.5);
		data->ply->turn_direction = -1;
	}
	else if (key == AROW_RIGHT)
	{
		data->ply->rotation_speed = degreeto_radian(3.5);
		data->ply->turn_direction = 1;
	}
	else if (key == A_KEY)
		data->mm = -1;
	else if (key == D_KEY)
		data->mm = +1;
	return (0);
}
//----------------------------------------------------------- key release
int	kay_releass(int key, t_data *data){
	if (key == S_KEY || key == W_KEY)
			data->ply->walk_direction = 0;
	else if (key == AROW_LEFT || key == AROW_RIGHT)
		data->ply->turn_direction = 0;
	else if (key == A_KEY)
		data->mm = 0;
	else if (key == D_KEY)
		data->mm = 0;
	return (0);
}
//--------------------------------------------------- draw all
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
		data->ply->rotation_speed = degreeto_radian(2.5);
		if(data->init_x_mouse - x < 0)
			data->ply->turn_direction = 1;
		else if(data->init_x_mouse - x > 0)
			data->ply->turn_direction = -1;
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
		data->ply->turn_direction = 0;
	}
	return(0);
}
//-------------------------------------------------
double	percent_function(double value, double max_value)
{
	double percent = 100 / (max_value / value);
	return(percent);
}
//----------------------------------------------
int shadowing_function(int color, double percent)
{
	int red;
	int green;
	int blue;

	red = color >> 16;
	red &= 255;
	green = color >> 8;
	green &= 255;
	blue = color >> 0;
	blue &= 255;
	red /= (100 + percent) / 100;
	green /= (100 + percent) / 100;
	blue /= (100 + percent) / 100;
	return(red << 16 | green << 8 | blue << 0);
}