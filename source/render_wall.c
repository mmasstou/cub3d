/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 17:32:25 by mmasstou          #+#    #+#             */
/*   Updated: 2022/09/11 10:10:15 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_wall(t_data *data, t_rays *ray, int x, int y)
{
	int	jndex;
	int	color;
	int	y_end_point;

	y_end_point = ray->wall_strip_height;
	if (y_end_point > H)
		y_end_point = H;
	jndex = (y + y_end_point);
	while (y <= jndex)
	{
		color = get_texture_color(ray, data, y);
		my_mlx_pixel_put(x, y, data, color);
		y++;
	}
}

void	rendering_wall(t_data *data, t_rays *rays, int ray_id)
{
	double	ray_distance;
	double	distance_project_plane;
	int		y_start_point;

	ray_distance = rays->distance * cos(\
	rays->angle - data->player->rotation_angle);
	distance_project_plane = ((W / 2) / tan(data->player->fov / 2));
	rays->wall_strip_height = \
	((data->unit * distance_project_plane) / ray_distance);
	y_start_point = (H / 2) - (rays->wall_strip_height / 2);
	if (y_start_point < 0)
		y_start_point = 0;
	draw_wall(\
	data, rays, ray_id, y_start_point);
}
