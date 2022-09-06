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

double distance_between_points(double x, double y, double angle)
{
	// return (sqrt(((x1 - x) * (x1 - x)) + ((y1 - y) * (y1 - y))));
	return ((y - x) / cos(angle));
}

double distance_between_points1(double x, double y, double x1, double y1)
{
	return (sqrt(((x1 - x) * (x1 - x)) + ((y1 - y) * (y1 - y))));
	// return ((y - x) / cos(angle));
}

void normalize_angle(double *angle){
	*angle = fmod(*angle, (2 * M_PI));
	if (*angle < 0)
		*angle += (2 * M_PI);
}

t_rays	*init_ray(t_data *data, double angle){
	t_rays *ray;

	ray = (t_rays *)malloc(sizeof(t_rays));
	if (!ray)
		_error("can't malloc ray");
	ray->angle = angle;
	normalize_angle(&(ray->angle));
	data->is_facing_down = (ray->angle >= 0 && ray->angle <= M_PI);
	data->is_facing_up = !data->is_facing_down;
	data->is_facing_right = (ray->angle < (0.5 * M_PI) || ray->angle > (1.5 * M_PI));
	data->is_facing_left = !data->is_facing_right;
	ray->distance = 0;
	ray->wall_hit.x = 0;
	ray->wall_hit.y = 0;
	ray->hit = false;
	ray->wasHithorizontal = false;
	ray->wasHitVertical = false;
	ray->found_horizontal_wall = false;
	ray->found_vertical_wall = false;
	ray->player.x = data->ply->x_pos * data->unit;
	ray->player.y = data->ply->y_pos * data->unit;
	ray->next = NULL;
	return (ray);
}


/*
TODO :
*
	? --&-- Horizontal coord --&-- 
	! --& -> calcul first intercept[x,y]
	! --& -> calcul  steps[x,y]
	! --& ->  finding position to Wall [x,y]
	! --& -> get distence 
	? --&-- Vertical coord --&--
	! --& -> calcul first intercept[x,y]
	! --& -> calcul  steps[x,y]
	! --& ->  finding position to Wall [x,y]
	! --& -> get distence 
	? find a fianal postion & distance

*/ 

/* 
*/
/* 
*/

t_rays	*cating_rays(t_data *data, double angle)
{
	t_rays		*ray;
	t_position intercept;
	t_position step;
	double nbr;
	double horizontall_distance = 0;
	double vertical_distance = 0;

	ray = init_ray(data, angle);
	
	//! HORIZONTALL RAY GRID
	//? intercept y
	
	intercept.y = floor(ray->player.y / data->unit) * data->unit;
	if (data->is_facing_down)
		intercept.y += data->unit;
	//? intercept x
	intercept.x = ray->player.x + (intercept.y - ray->player.y) / tan(ray->angle);

	
	//*Steps
	//	?step y
	step.y = data->unit;
	if (data->is_facing_up)
		step.y *= -1;
	//	?step x
	step.x = data->unit / tan(ray->angle);
	if ((data->is_facing_left && step.x > 0))
		step.x *= -1;
	if ((data->is_facing_right && step.x < 0))
		step.x *= -1;

		
	//  finding wall hit
	while (true)
	{
		nbr = intercept.y;
		if (data->is_facing_up)
			nbr --;
		if (wall_collaction(intercept.x / data->unit, nbr / data->unit, data) == 1)
		{
			ray->found_horizontal_wall = true;
			ray->horizontal_wall_hit.x = intercept.x;
			ray->horizontal_wall_hit.y = intercept.y;
			break;
		}
		else
		{
			intercept.x += step.x;
			intercept.y += step.y;
		}
	}
	//! VERTICAL RAY GRID
	//? intercept x
	intercept.x = floor(ray->player.x / data->unit) * data->unit;
	if (data->is_facing_right)
		intercept.x += data->unit;
	//? intercept y
	intercept.y = ray->player.y + (intercept.x - ray->player.x) * tan(ray->angle);

	//? step x
	step.x = data->unit;
	if (data->is_facing_left)
		step.x *= -1;
	//? step y
	step.y = data->unit * tan(ray->angle);
	if ((data->is_facing_up && step.y > 0))
		step.y *= -1;
	if ((data->is_facing_down && step.y < 0))
		step.y *= -1;
	//  finding wall hit > (intercept.x >= 0 && intercept.x <= H) && (intercept.y >= 0 && intercept.y <= W)
	while (true)
	{
		nbr = intercept.x ;
		if (data->is_facing_left)
			nbr -= 1;
		if (wall_collaction(nbr / data->unit, intercept.y / data->unit, data) == 1)
		{
			ray->found_vertical_wall = true;
			ray->vertical_wall_hit.x = intercept.x ;
			ray->vertical_wall_hit.y = intercept.y;
			break;
		}
		else
		{
			intercept.x  += step.x;
			intercept.y += step.y;
		}	
	}
	//  calculate both horizontal and vertical distance
	if (ray->found_horizontal_wall)
	{
		horizontall_distance = distance_between_points1(
			ray->player.x,
			ray->player.y,
			ray->horizontal_wall_hit.x,
			ray->horizontal_wall_hit.y
		);
		// horizontall_distance = distance_between_points(
		// 	ray->player.x,
		// 	ray->horizontal_wall_hit.x,
		// 	ray->angle
		// );
	}
	if (ray->found_vertical_wall)
	{
		vertical_distance = distance_between_points1(
			ray->player.x,
			ray->player.y,
			ray->vertical_wall_hit.x,
			ray->vertical_wall_hit.y
		);
		// vertical_distance = distance_between_points(
		// 	ray->player.x,
		// 	ray->vertical_wall_hit.x,
		// 	ray->angle
		// );
	}
	// get min distance
	if (horizontall_distance <= vertical_distance)
	{
		ray->distance = horizontall_distance;
		ray->wall_hit.x = ray->horizontal_wall_hit.x;
		ray->wall_hit.y = ray->horizontal_wall_hit.y;
		ray->wasHithorizontal = true;
	}
	else
	{
		ray->distance = vertical_distance;
		ray->wall_hit.x = ray->vertical_wall_hit.x;
		ray->wall_hit.y = ray->vertical_wall_hit.y;
		ray->wasHitVertical = true;
	}
	if (ray->distance < DISTANCE_OF_VIEW)
		ray->hit = true;
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
int ray_caste(t_data *data)
{
	int colid;
	double ray_angle;
	t_rays *ray;

	data->rays = NULL;
	ray_angle = data->ply->rotation_angle - FOV / 2;
	colid = 0;
	while (colid <= NBR_RAYS)
	{
		ray = cating_rays(data, ray_angle);
		rendering_walll(data, ray, colid);
		adding_ray(&(data->rays), ray);
		colid++;
		ray_angle += FOV_INC;
	}
	return (0);
}