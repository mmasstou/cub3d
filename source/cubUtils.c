/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubUtils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 12:31:27 by mmasstou          #+#    #+#             */
/*   Updated: 2022/09/11 13:15:40 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	*ft_reassign(void *oldptr, void *newptr)
{
	free(oldptr);
	return (newptr);
}

double	degreeto_radian(float angle)
{
	return (angle * (M_PI / 180));
}

int	ft_rgb(int t, int r, int g, int b)
{
	return ((((t * 255) / 100) << 24) | (r << 16) | (g << 8) | b);
}

void	normalize_angle(double *angle)
{
	*angle = fmod(*angle, (2 * M_PI));
	if (*angle < 0)
		*angle += (2 * M_PI);
}

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
