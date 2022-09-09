/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 12:42:42 by mmasstou          #+#    #+#             */
/*   Updated: 2022/09/09 18:25:52 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_texture_color(t_rays *ray, t_data *data, int y)
{
	t_pos		tex_offset;
	double		x;
	int			color;
	t_texture	*tmp;

	tmp = get_texture(data->tex, ray);
	if (!tmp)
		return (0);
	if (ray->was_hit_vertical)
		tex_offset.x = ray->wall_hit.y / data->unit;
	else
		tex_offset.x = ray->wall_hit.x / data->unit;
	tex_offset.x = tex_offset.x - floor(tex_offset.x);
	tex_offset.x *= tmp->width;
	x = y + (ray->wall_strip_height / 2) - (H / 2);
	if (x < 0)
		x = 0;
	tex_offset.y = x * ((double)tmp->height / ray->wall_strip_height);
	tex_offset.y = floor(tex_offset.y);
	tex_offset.y *= tmp->width;
	color = tmp->buff[((int)tex_offset.y + (int)tex_offset.x)];
	return (color);
}
