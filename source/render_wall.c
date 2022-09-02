/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 17:32:25 by mmasstou          #+#    #+#             */
/*   Updated: 2022/09/02 12:34:47 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    draw_wall(t_data *data, double x, double y,int wall_strip_width, double wall_strip_height)
{
	int index;
	int jndex;
	int old__y;
	
	index = (x + wall_strip_width);
	jndex = (y + wall_strip_height); 
	old__y = y;
	while (x <= index)
	{
		y = old__y;
		while (y <= jndex)
			my_mlx_pixel_put(x, y++, data, data->ply->color);
		x++;
	}
}

void	rendering_walll(t_data *data, t_rays *rays, int col_id)
{
	double ray_distance;
	double distance_project_plane;
	double wall_strip_height;

	ray_distance = rays->distance * cos(rays->angle - data->ply->rotation_angle);
	distance_project_plane = ((W / 2) / tan(FOV / 2));
	wall_strip_height = (data->unit / ray_distance) * distance_project_plane;
	// if (wall_strip_height > H)
	// 	wall_strip_height = H;
	data->ply->color = ft_rgb(50, 255, 255, 255);
	if (rays->wasHitVertical)
		data->ply->color = ft_rgb(10, 238, 238, 238);
	draw_wall(
		data,
		col_id * WALL_STRIPE_WITH,
		(H / 2) - (wall_strip_height / 2),
		WALL_STRIPE_WITH,
		wall_strip_height
	);
}

void	rendering_wall(t_data *data, t_rays *rays)
{
	t_rays	*tmp;
	int index;
	double ray_distance;
	double distance_project_plane;
	double wall_strip_height;


	tmp = rays;
	index = 0;
	while (tmp)
	{
		ray_distance = tmp->distance * cos(tmp->angle - data->ply->rotation_angle);
		distance_project_plane = (W / 2) / tan(FOV / 2);
		wall_strip_height = (data->unit / ray_distance) * distance_project_plane;
		if (wall_strip_height > H)
			wall_strip_height = H;
		data->ply->color = ft_rgb(50, 255, 255, 255);
		if (tmp->wasHitVertical)
			data->ply->color = ft_rgb(10, 238, 238, 238);
		draw_wall(
			data,
			index * WALL_STRIPE_WITH,
			(H / 2) - (wall_strip_height / 2),
			WALL_STRIPE_WITH,
			wall_strip_height
		);
		index ++;
		tmp = tmp ->next;
	}
}