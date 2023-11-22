/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellakr <abellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 11:49:57 by abellakr          #+#    #+#             */
/*   Updated: 2022/09/11 11:54:43 by abellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	mouse_move(int x, int y, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (data->pressed == TRUE && x < W && x >= 0 && y < H && y >= 0)
	{
		data->player->rotation_speed = degreeto_radian(2.5);
		if (data->init_x_mouse - x < 0)
			data->player->turn_direction = 1;
		else if (data->init_x_mouse - x > 0)
			data->player->turn_direction = -1;
	}
	return (0);
}

int	mouse_press(int button, int x, int y, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (button == 1 && x < W && x >= 0 && y < H && y >= 0)
	{
		data->pressed = TRUE;
		data->init_x_mouse = x;
	}
	return (0);
}

int	mouse_release(int button, int x, int y, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (button == 1 && x < W && x >= 0 && y < H && y >= 0)
	{
		data->pressed = FALSE;
		data->player->turn_direction = 0;
	}
	else if (x > W || x < 0 || y > H || y < 0)
	{
		data->pressed = FALSE;
		data->player->turn_direction = 0;
	}
	return (0);
}
