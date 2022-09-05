/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 17:32:25 by mmasstou          #+#    #+#             */
/*   Updated: 2022/09/02 16:53:50 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    draw_wall(t_data *data, t_rays *ray, int x, int y, int wall_strip_height)
{
	int jndex;
	
	jndex = (y + wall_strip_height); 
	while (y <= jndex)
	{
		// printf("y == %f, %f\n", y, x);
		my_mlx_pixel_put(x, y, data, get_texture_color(ray, data, y, wall_strip_height));
		y++;
	}
}
// void	get_pixel_color(t_data *data, double distance)
// {
// 	distance = (int)distance % 255;
// 	data->ply->color = ft_rgb(255 / distance, 255 / distance, 255 / distance, 255 / distance);
// }
void	rendering_walll(t_data *data, t_rays *rays, int ray_id)
{
	double ray_distance;
	double distance_project_plane;
	// double wall_strip_height;
	int y_start_point;
	int y_end_point;

	ray_distance = rays->distance * cos(rays->angle - data->ply->rotation_angle);
	distance_project_plane = ((W / 2) / tan(FOV / 2));
	rays->wall_strip_height = (data->unit / ray_distance) * distance_project_plane;
	// wall_strip_height = H / (ray_distance / data->unit);
	y_start_point = (H / 2) - (rays->wall_strip_height / 2);
	if (y_start_point < 0)
		y_start_point = 0;
	
	y_end_point = rays->wall_strip_height;
	if (y_end_point > H)
		y_end_point = H;
	// get_pixel_color(data, rays->distance);
	draw_wall(
		data,
		rays,
		ray_id,
		y_start_point,
		y_end_point
	);
}

// void	rendering_wall(t_data *data, t_rays *rays)
// {
// 	t_rays	*tmp;
// 	int index;
// 	double ray_distance;
// 	double distance_project_plane;
// 	double wall_strip_height;

// 	tmp = rays;
// 	index = 0;
// 	while (tmp)
// 	{
// 		ray_distance = tmp->distance * cos(tmp->angle - data->ply->rotation_angle);
// 		distance_project_plane = (W / 2) / tan(FOV / 2);
// 		wall_strip_height = (data->unit / ray_distance) * distance_project_plane;
// 		if (wall_strip_height > H)
// 			wall_strip_height = H;
// 		data->ply->color = ft_rgb(50, 255, 255, 255);
// 		if (tmp->wasHitVertical)
// 			data->ply->color = ft_rgb(10, 238, 238, 238);
// 		draw_wall(
// 			data,
// 			index * WALL_STRIPE_WITH,
// 			(H / 2) - (wall_strip_height / 2),
// 			wall_strip_height
// 		);
// 		index ++;
// 		tmp = tmp ->next;
// 	}
// }