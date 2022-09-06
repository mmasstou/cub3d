/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Hooks_and_Events.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 18:35:28 by mmasstou          #+#    #+#             */
/*   Updated: 2022/09/02 18:23:50 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
	draw_ceilling_floor(data);
	init_textures(data);
	ray_caste(data);
	// rendering_wall(data, data->rays);
	draw__map(data);
	draw__fov(data);
	draw__player(data);
	// plotCircle(W - 120,H - 90,50, data);
	// draw__pov(data);
    // mlx_put_image_to_window (data->mlx_vars->mlx_ptr, data->mlx_vars->mlx_window, data->tex->mlx_image, 0, 0);
    mlx_put_image_to_window (data->mlx_vars->mlx_ptr, data->mlx_vars->mlx_window, data->mlx_vars->mlx_image, 0, 0);
	mlx_hook(data->mlx_vars->mlx_window, KeyPress, KeyPressMask, kay_press, data);
	mlx_hook(data->mlx_vars->mlx_window, KeyRelease, KeyReleaseMask, kay_releass, data);
	mlx_hook (data->mlx_vars->mlx_window, 17, 1L << 0, close_cross, data);
	// mlx_hook (data->mlx_vars->mlx_window, 6, 1L << 0, mouse_move, data);
	// mlx_mouse_hook (data->mlx_vars->mlx_window,mouse_move_clik, data);
	mlx_loop_hook(data->mlx_vars->mlx_ptr, looop__hooking, data);
    mlx_loop (data->mlx_vars->mlx_ptr);
}
 
void	re_draw__(t_data *data){
	mlx_clear_window(data->mlx_vars->mlx_ptr, data->mlx_vars->mlx_window);
	mlx_destroy_image(data->mlx_vars->mlx_ptr,data->mlx_vars->mlx_image);
    data->mlx_vars->mlx_image = mlx_new_image(data->mlx_vars->mlx_ptr, W, H);
    data->mlx_vars->buffer = mlx_get_data_addr (data->mlx_vars->mlx_image, &data->mlx_vars->bpp, &data->mlx_vars->line_lenght, &data->mlx_vars->endian);
    draw_ceilling_floor(data);
	ray_caste(data);
	// rendering_wall(data, data->rays);
	draw__map(data);
	draw__fov(data);
	draw__player(data);
	// plotCircle(W - 120,H - 90,50, data);
	// draw__pov(data);
    // mlx_put_image_to_window (data->mlx_vars->mlx_ptr, data->mlx_vars->mlx_window, data->tex->mlx_image, 0, 0);
    mlx_put_image_to_window (data->mlx_vars->mlx_ptr, data->mlx_vars->mlx_window, data->mlx_vars->mlx_image, 0, 0);
}

int looop__hooking(t_data *data){
	player_update(&data);
	re_draw__(data);
	return (0);
}
//

int	close_cross(void *param)
{
	(void)param;
	exit (0);
}

int mouse_move(int x, int y, t_data *param)
{
	// int diff;

	// if (x > 0 && x < W && y> 0 &&  y < H)
	// {
	// 	diff = param->ply->win_middle_width - x;
	// 	printf("diff +|%d\n", diff);
	// 	if (diff < 0 && param->ply->mouse_clik == 1)
	// 		param->ply->turn_direction_mouse = -1;
	// 	if (diff > 0 && param->ply->mouse_clik == 1)
	// 		param->ply->turn_direction_mouse = 1;
	// }
	// else
	// {
	// 	param->ply->turn_direction_mouse = 0;
	// }
	printf("%d, %d\n", x, y);
	printf("%s\n", param->ea);
	return (0);
}

int mouse_move_clik(int x, int y, t_data *param)
{
	(void)param;
	if (x == 1)
	{
		// param->ply->mouse_clik = true;
		printf("mouse (%d, %d)\n", x, y);
		// printf("%s\n", param->ea);
	}
	return (0);
}

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
		data->ply->turn_direction = -1;
	else if (key == AROW_RIGHT)
		data->ply->turn_direction = 1;
	else if (key == A_KEY)
		data->mm = -1;
	else if (key == D_KEY)
		data->mm = +1;
	return (0);
}

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