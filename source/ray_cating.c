/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cating.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellakr <abellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 18:35:47 by mmasstou          #+#    #+#             */
/*   Updated: 2022/09/10 14:06:20 by abellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_rays	*cating_rays(t_data *data, double angle)
{
	t_rays	*ray;
	t_pos	intercept;
	t_pos	step;
	t_pos	distance;

	ray = init_ray(data, angle);
	intercept = find_intercept(data, ray, HORIZO_TYPE);
	step = find_horizontal_step(data, ray);
	find_horizontal_hit_point(data, ray, intercept, step);
	intercept = find_intercept(data, ray, VERTIC_TYPE);
	step = find_vertical_step(data, ray);
	find_vertical_hit_point(data, ray, intercept, step);
	distance = get_init_distance(ray);
	get_final_distance(ray, distance);
	return (ray);
}

void	adding_ray(t_rays **lst, t_rays *new)
{
	t_rays	*n;

	if (*lst == NULL)
		*lst = new;
	else
	{
		n = *lst;
		while (n->next != NULL)
			n = n->next;
		n->next = new;
	}
}

int	ray_caste(t_data *data)
{
	int		colid;
	double	ray_angle;
	t_rays	*ray;

	data->rays = NULL;
	data->player->fov_inc = data->player->fov / data->nbr_rays;
	ray_angle = data->player->rotation_angle - data->player->fov / 2;
	colid = 0;
	while (colid <= data->nbr_rays)
	{
		ray = cating_rays(data, ray_angle);
		rendering_wall(data, ray, colid);
		adding_ray(&(data->rays), ray);
		colid++;
		ray_angle += data->player->fov_inc;
	}
	return (0);
}
