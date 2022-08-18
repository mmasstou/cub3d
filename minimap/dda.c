/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 13:10:35 by mmasstou          #+#    #+#             */
/*   Updated: 2022/08/18 04:45:43 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	dda(float x, float y, t_data *data)
{
	int		step;
	float	xinc;
	float	yinc;
	
	data->deltax = data->nextx - x;
	data->deltay = data->nexty - y;
	step = STEP(abs(data->deltax), abs(data->deltay));
	xinc = data->deltax / step;
	yinc = data->deltax / step;
	while (step >= 0)
	{
		my_mlx_pixel_put(x, y + (H - (data->h * data->zoom)) ,data, 7398437);
		x += xinc;
		y += yinc;
		step--;
	}
	return (0);
}

int	row_dda(float x, float y, float next_x, float next_y, t_data *data)
{
	int		step;
	float	xinc;
	float	yinc;
	float	i;
	float	j;
	
	data->deltax = next_x - x;
	data->deltay = next_y - y;
	if (abs(data->deltax) > abs(data->deltay))
		step = abs(data->deltax);
	else
		step = abs(data->deltay);
	xinc = data->deltax / step;
	yinc = data->deltax / step;
	i = x;
	j = y;
	while (step >= 0)
	{
		my_mlx_pixel_put(i, j ,data, 15797260);
		i += xinc;
		j += yinc;
		step--;
	}
	return (0);
}