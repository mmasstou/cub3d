/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cating.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 18:35:47 by mmasstou          #+#    #+#             */
/*   Updated: 2022/09/02 10:32:13 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	find_horizontal_hit_point(
	t_data *data, t_rays *ray, t_pos intercept, t_pos step)
{
	double	nbr;
	int		unit;

	unit = data->unit;
	while (true)
	{
		nbr = intercept.y;
		if (data->player->is_facing_up)
			nbr --;
		if (wall_collaction(intercept.x / unit, nbr / unit, data) == 1)
		{
			ray->found_horizontal_wall = true;
			ray->horizontal_wall_hit.x = intercept.x;
			ray->horizontal_wall_hit.y = intercept.y;
			break ;
		}
		else
		{
			intercept.x += step.x;
			intercept.y += step.y;
		}
	}
}

void	find_vertical_hit_point(
	t_data *data, t_rays *ray, t_pos intercept, t_pos step)
{
	double	nbr;
	int		unit;

	unit = data->unit;
	while (true)
	{
		nbr = intercept.x ;
		if (data->player->is_facing_left)
			nbr -= 1;
		if (wall_collaction(nbr / unit, intercept.y / unit, data) == 1)
		{
			ray->found_vertical_wall = true;
			ray->vertical_wall_hit.x = intercept.x ;
			ray->vertical_wall_hit.y = intercept.y;
			break ;
		}
		else
		{
			intercept.x += step.x;
			intercept.y += step.y;
		}	
	}
}

t_pos	get_init_distance(t_rays *ray)
{
	t_pos	distance;

	if (ray->found_horizontal_wall)
		distance.y = distance_between_points(\
		ray->player.x, ray->horizontal_wall_hit.x, ray->angle);
	if (ray->found_vertical_wall)
		distance.x = distance_between_points(\
		ray->player.x, ray->vertical_wall_hit.x, ray->angle);
	return (distance);
}

void	get_final_distance(t_rays *ray, t_pos distance)
{
	if (distance.y <= distance.x)
	{
		ray->distance = distance.y;
		ray->wall_hit.x = ray->horizontal_wall_hit.x;
		ray->wall_hit.y = ray->horizontal_wall_hit.y;
		ray->was_hit_horizontal = true;
		ray->was_hit_vertical = false;
	}
	else
	{
		ray->distance = distance.x;
		ray->wall_hit.x = ray->vertical_wall_hit.x;
		ray->wall_hit.y = ray->vertical_wall_hit.y;
		ray->was_hit_vertical = true;
		ray->was_hit_horizontal = false;
	}
}
