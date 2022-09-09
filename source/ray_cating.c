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

double	distance_between_points(double x, double y, double angle)
{
	return ((y - x) / cos(angle));
}

double	distance_between_points1(double x, double y, double x1, double y1)
{
	return (sqrt(((x1 - x) * (x1 - x)) + ((y1 - y) * (y1 - y))));
}

void	normalize_angle(double *angle)
{
	*angle = fmod(*angle, (2 * M_PI));
	if (*angle < 0)
		*angle += (2 * M_PI);
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

t_position	find_intercept(t_data *data, t_rays *ray, int type)
{
	t_position	intercept;
	t_position	p;

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

t_position	find_vertical_step(t_data *data, t_rays *ray)
{
	t_position	step;

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

t_position	find_horizontal_step(t_data *data, t_rays *ray)
{
	t_position	step;

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

void	find_horizontal_hit_point(
	t_data *data, t_rays *ray, t_position intercept, t_position step)
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
	t_data *data, t_rays *ray, t_position intercept, t_position step)
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

t_position	get_init_distance(t_rays *ray)
{
	t_position	distance;

	if (ray->found_horizontal_wall)
		distance.y = distance_between_points(\
		ray->player.x, ray->horizontal_wall_hit.x, ray->angle);
	if (ray->found_vertical_wall)
		distance.x = distance_between_points(\
		ray->player.x, ray->vertical_wall_hit.x, ray->angle);
	return (distance);
}

void	get_final_distance(t_rays *ray, t_position distance)
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

t_rays	*cating_rays(t_data *data, double angle)
{
	t_rays		*ray;
	t_position	intercept;
	t_position	step;
	t_position	distance;

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

//  intersections
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
		rendering_walll(data, ray, colid);
		adding_ray(&(data->rays), ray);
		colid++;
		ray_angle += data->player->fov_inc;
	}
	return (0);
}
