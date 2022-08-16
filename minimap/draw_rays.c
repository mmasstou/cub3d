/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 16:54:41 by mmasstou          #+#    #+#             */
/*   Updated: 2022/08/15 23:14:01 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	draw_rays(t_data *data)
{
	data->nextx = 0;
	data->nexty = 0;
	dda(data->x_player * data->zoom, data->y_player * data->zoom, data);
	printf("%f\n", data->x_player);
	return (0);
}