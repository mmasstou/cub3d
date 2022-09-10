/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Hooks_and_Events.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellakr <abellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 18:35:28 by mmasstou          #+#    #+#             */
/*   Updated: 2022/09/10 14:49:15 by abellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	looop__hooking(t_data *data)
{
	if(data->pressed == true)
		data->player->rotation_speed = degreeto_radian(3);
	else if (data->pressed == false)
		data->player->rotation_speed = degreeto_radian(5);
	player_update(&data);
	re_draw__(data);
	return (0);
}

int	close_cross(t_data *param)
{
	mlx_destroy_image(param->mlx_vars->mlx_ptr, param->mlx_vars->mlx_image);
	mlx_destroy_window(param->mlx_vars->mlx_ptr, param->mlx_vars->mlx_window);
	free_params(param);
	free_array(param->map);
	free(param->player);
	free(param->rays);
	free_texture(param->tex);
	exit (0);
}

int	kay_press(int key, t_data *data)
{
	if (key == 53)
	{
		mlx_destroy_image(data->mlx_vars->mlx_ptr, data->mlx_vars->mlx_image);
		mlx_destroy_window(data->mlx_vars->mlx_ptr, data->mlx_vars->mlx_window);
		free_params(data);
		free_array(data->map);
		free(data->player);
		free(data->rays);
		free_texture(data->tex);
		exit (0);
	}
	else if (key == S_KEY || key == AROW_DOWN)
		data->player->walk_direction.y = -1;
	else if (key == W_KEY || key == AROW_UP)
		data->player->walk_direction.y = 1;
	else if (key == AROW_LEFT)
		data->player->turn_direction = -1;
	else if (key == AROW_RIGHT)
		data->player->turn_direction = 1;
	else if (key == A_KEY)
		data->player->walk_direction.x = -1;
	else if (key == D_KEY)
		data->player->walk_direction.x = +1;
	return (0);
}

int	kay_releass(int key, t_data *data)
{
	if (key == S_KEY || key == AROW_DOWN)
		data->player->walk_direction.y = 0;
	else if (key == W_KEY || key == AROW_UP)
		data->player->walk_direction.y = 0;
	else if (key == AROW_LEFT)
		data->player->turn_direction = 0;
	else if (key == AROW_RIGHT)
		data->player->turn_direction = 0;
	else if (key == A_KEY)
		data->player->walk_direction.x = 0;
	else if (key == D_KEY)
		data->player->walk_direction.x = 0;
	return (0);
}
