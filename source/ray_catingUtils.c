/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_catingUtils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellakr <abellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 18:35:47 by mmasstou          #+#    #+#             */
/*   Updated: 2022/09/10 14:16:20 by abellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double	distance_between_points(double x, double y, double angle)
{
	return ((y - x) / cos(angle));
}

t_rays	*init_ray(t_data *data, double angle)
{
	t_rays		*ray;
	t_player	*p;
	double		bita;

	ray = (t_rays *)malloc(sizeof(t_rays));
	if (!ray)
		_error("can't malloc ray");
	ray->angle = angle;
	p = data->player;
	normalize_angle(&(ray->angle));
	bita = ray->angle;
	p->is_facing_down = (bita >= 0 && bita <= M_PI);
	p->is_facing_up = !p->is_facing_down;
	p->is_facing_right = (bita < (0.5 * M_PI) || bita > (1.5 * M_PI));
	p->is_facing_left = !p->is_facing_right;
	ray->was_hit_horizontal = false;
	ray->was_hit_vertical = false;
	ray->found_horizontal_wall = false;
	ray->found_vertical_wall = false;
	ray->player.x = p->pos.x * data->unit;
	ray->player.y = p->pos.y * data->unit;
	ray->next = NULL;
	return (ray);
}

t_pos	find_intercept(t_data *data, t_rays *ray, int type)
{
	t_pos	intercept;
	t_pos	p;

	p = ray->player;
	if (type == HORIZO_TYPE)
	{
		intercept.y = floor(p.y / data->unit) * data->unit;
		if (data->player->is_facing_down)
			intercept.y += data->unit;
		intercept.x = p.x + (intercept.y - p.y) / tan(ray->angle);
	}
	else
	{
		intercept.x = floor(p.x / data->unit) * data->unit;
		if (data->player->is_facing_right)
			intercept.x += data->unit;
		intercept.y = p.y + (intercept.x - p.x) * tan(ray->angle);
	}
	return (intercept);
}

t_pos	find_vertical_step(t_data *data, t_rays *ray)
{
	t_pos	step;

	step.x = data->unit;
	if (data->player->is_facing_left)
		step.x *= -1;
	step.y = data->unit * tan(ray->angle);
	if ((data->player->is_facing_up && step.y > 0))
		step.y *= -1;
	if ((data->player->is_facing_down && step.y < 0))
		step.y *= -1;
	return (step);
}

t_pos	find_horizontal_step(t_data *data, t_rays *ray)
{
	t_pos	step;

	step.y = data->unit;
	if (data->player->is_facing_up)
		step.y *= -1;
	step.x = data->unit / tan(ray->angle);
	if ((data->player->is_facing_left && step.x > 0))
		step.x *= -1;
	if ((data->player->is_facing_right && step.x < 0))
		step.x *= -1;
	return (step);
}
