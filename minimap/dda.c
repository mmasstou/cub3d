/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 13:10:35 by mmasstou          #+#    #+#             */
/*   Updated: 2022/08/15 22:13:44 by mmasstou         ###   ########.fr       */
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