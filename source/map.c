/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 18:35:37 by mmasstou          #+#    #+#             */
/*   Updated: 2022/09/02 12:15:41 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(int x, int y, t_data *data, int color)
{
	char	*dst;

	if ((x >= 0 && x < W) && (y >= 0 && y < H))
	{
		dst = data->mlx_vars->buffer + \
		(y * data->mlx_vars->line_lenght + x * (data->mlx_vars->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

int	wall_collaction(float index, float jndex, t_data *data)
{
	int	x;
	int	y;
	int	array_len;
	int	str_len;

	array_len = ft_arraylen(data->map);
	x = floor(index);
	y = floor(jndex);
	if (y > array_len || y < 0)
		return (1);
	if (y >= 0 && data->map[y] != NULL)
	{
		str_len = ft_strlen(data->map[y]);
		if (x > str_len || x < 0)
			return (1);
		if (data->map[y][x] == '1' || data->map[y][x] == ' ')
			return (1);
		else if (data->map[y][x] == '0' || \
		ft_strchr("SWNE", data->map[y][x]) != NULL)
			return (0);
	}
	return (0);
}
