/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 14:24:41 by mmasstou          #+#    #+#             */
/*   Updated: 2022/08/17 14:53:18 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	re_draw(t_data *data)
{
	mlx_clear_window(data->mlx_vars->mlx_ptr, data->mlx_vars->mlx_window);
	mlx_destroy_image(data->mlx_vars->mlx_ptr,data->mlx_vars->mlx_image);
    data->mlx_vars->mlx_image = mlx_new_image(data->mlx_vars->mlx_ptr, W, H);
    data->mlx_vars->buffer = mlx_get_data_addr (data->mlx_vars->mlx_image, &data->mlx_vars->bpp, &data->mlx_vars->line_lenght, &data->mlx_vars->endian);
    drawing_minimap(data);
    drawing_minimapp(data);
    mlx_put_image_to_window (data->mlx_vars->mlx_ptr, data->mlx_vars->mlx_window, data->mlx_vars->mlx_image, 0, 0);
}

int	move_player(int key, t_data *data)
{
	if (key == 53)
	{
		mlx_destroy_image (data->mlx_vars->mlx_ptr, data->mlx_vars->mlx_image);
		mlx_destroy_window (data->mlx_vars->mlx_ptr, data->mlx_vars->mlx_window);
		exit (0);
	}
	if (key == S_KEY || key == 125)
	{
		if ( data->map[(int)data->y_player] &&( data->map[(int)data->y_player][(int)data->x_player] == '0'))
			data->p_up += 5.6;
	}
	if (key == W_KEY || key == 126)
	{
		if (data->map[(int)data->y_player] && data->map[(int)(data->y_player - 0.0005)][(int)data->x_player] == '0')
			data->p_up -= 5.6;
	}
	if (key == A_KEY || key == 123)
		data->bita -= .2;
	if (key == D_KEY || key == 124)
		data->bita += .2;
	re_draw(data);
	return (0);
}