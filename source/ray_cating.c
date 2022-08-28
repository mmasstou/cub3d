#include "../includes/cub3d.h"

double distance_between_points(double x, double y, double x1, double y1)
{
	return (sqrt(((x1 - x) * (x1 - x)) + ((y1 - y) * (y1 - y))));
}

void normalize_angle(double *angle){
	*angle = fmod(*angle, (2 * M_PI));
	if (*angle < 0)
		*angle += (2 * M_PI);
}

t_rays	*init_ray(double angle){
	t_rays *ray;

	ray = (t_rays *)malloc(sizeof(t_rays));
	if (!ray)
		_error("can't malloc ray");
	ray->angle = angle;
	normalize_angle(&(ray->angle));
	ray->distance = 0;
	ray->wall_hit.x = 0;
	ray->wall_hit.y = 0;
	ray->wasHithorizontal = false;
	ray->wasHitVertical = false;
	ray->next = NULL;
	return (ray);
}

/*
TODO :
*
? Horizontal 
! --& -> calcul first intercept[x,y]
! --& -> calcul  steps[x,y]
! --& ->  finding position to Wall [x,y]
! --& -> get distence 
? Vertical
! --& -> calcul first intercept[x,y]
! --& -> calcul  steps[x,y]
! --& ->  finding position to Wall [x,y]
! --& -> get distence 
? find a fianal postion & distance

*/ 

/* 
! --&-- Horizontal Intersection --&-- 
*/
t_pos	horizo_intercept__steps(t_pos *intercept, t_data *data, t_rays *ray)
{
	t_pos	step;

	intercept->y = floor(data->ply->y_pos / data->unit) * data->unit;
	if (data->is_facing_down)
		intercept->y += data->unit;
	intercept->x = data->ply->x_pos + ( intercept->y - data->ply->y_pos) / tan(ray->angle);
	step.y = data->unit;
	if (data->is_facing_up)
		step.y *= -1;
	step.x = data->unit / tan(ray->angle);
	if (data->is_facing_left && step.x > 0)
		step.x *= -1;
	if (data->is_facing_right && step.x < 0)
		step.x *= -1;
	return (step);
}

t_pos	vertical_intercept__steps(t_pos *intercept, t_data *data, t_rays *ray)
{
	t_pos	step;

	intercept->x = floor(data->ply->x_pos / data->unit) * data->unit;
	if (data->is_facing_right)
		intercept->x += data->unit;
	intercept->y = data->ply->y_pos + ( intercept->x - data->ply->x_pos) / tan(ray->angle);
	step.x = data->unit;
	if (data->is_facing_left)
		step.x *= -1;
	step.y = data->unit / tan(ray->angle);
	if (data->is_facing_up && step.y > 0)
		step.y *= -1;
	if (data->is_facing_down && step.y < 0)
		step.y *= -1;
	return (step);
}
/* 
! --&-- Vertical Intersection --&--
*/

t_pos	get_wall_touch(int type, t_data *data, t_rays *ray, t_pos (*f)(t_pos *, t_data *, t_rays *))
{
	t_pos intercept;
	t_pos step;
	t_pos wall_hit;
	int	index;
	int jndex;
	
	wall_hit.x = 0;
	wall_hit.y = 0;
	step = f(&intercept, data, ray);
	while (
		intercept.x >= 0 && intercept.x <= W && intercept.y >= 0 && intercept.y <= H
	)
	{
		if (type == HORIZO_TYPE)
		{
			jndex = intercept.y;
			if (data->is_facing_up)
				jndex -= 1;
			jndex /= data->unit;
			index = intercept.x / data->unit;
		}
		else if (type == VERTIC_TYPE)
		{
			jndex = intercept.y / data->unit;
			index = intercept.x;
			if (data->is_facing_left)
				index -= 1;
			index /= data->unit;
		}
		if (wall_collaction(index, jndex, data) == 1)
		{
			if (type == VERTIC_TYPE)
				ray->wasHitVertical = true;
			if (type == HORIZO_TYPE)
				ray->wasHithorizontal = true;
			wall_hit.x = intercept.x;
			wall_hit.y = intercept.y;
			break;
		}
		else
		{
			intercept.x += step.x;
			intercept.y += step.y;
		}
	}
	return (wall_hit);
}

t_rays	*cating_rays(t_data *data, double angle)
{
	t_rays *ray;
	t_pos horizotal_wall_touch;
	t_pos vertical_wall_touch;

	ray = init_ray(angle);
	data->is_facing_down = (angle > 0 && angle < M_PI);
	data->is_facing_up = !data->is_facing_down;
	data->is_facing_right = (angle < (0.5 * M_PI) || angle > (1.5 * M_PI));
	data->is_facing_left = !data->is_facing_right;

	horizotal_wall_touch = get_wall_touch(HORIZO_TYPE, data, ray, &horizo_intercept__steps);
	vertical_wall_touch = get_wall_touch(VERTIC_TYPE, data, ray, &vertical_intercept__steps);
	if (ray->wasHithorizontal)
	{
		data->horizontal_distance = distance_between_points(
			data->ply->x_pos,
			data->ply->y_pos,
			horizotal_wall_touch.x,
			horizotal_wall_touch.y
		);
	}
	else
		data->horizontal_distance = INT_MAX;
	if (ray->wasHitVertical)
	{
		data->vertical_distance = distance_between_points(
			data->ply->x_pos,
			data->ply->y_pos,
			vertical_wall_touch.x,
			vertical_wall_touch.y
		);
	}
	else
		data->vertical_distance = INT_MAX;
	if (data->horizontal_distance < data->vertical_distance)
	{
		ray->wall_hit.x = horizotal_wall_touch.x;
		ray->wall_hit.y = horizotal_wall_touch.y;
	}
	else
	{
		ray->wall_hit.x = vertical_wall_touch.x;
		ray->wall_hit.y = vertical_wall_touch.y;
	}
	if (data->horizontal_distance < data->vertical_distance)
		ray->distance = data->horizontal_distance;
	else
		ray->distance = data->vertical_distance;
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
int ray_caste(t_data *data){
	int colid;
	double ray_angle;
	double x1;
	double y1;
	t_rays *tmp;

	data->rays = NULL;
	ray_angle = data->ply->rotation_angle - (degreeto_radian(FOV) / 2);
	// normalize_angle(&ray_angle);
	colid = 0;
	while (colid <= NBR_RAYS)
	{
		adding_ray(&(data->rays), cating_rays(data, ray_angle));
		
		colid++;
		ray_angle += FOV_INC;
	}
	tmp = data->rays;
	while (tmp){
		x1 = data->ply->x_pos * data->unit;
		y1 = data->ply->y_pos * data->unit;
		data->x1 = x1;
		data->y1 = y1;
		data->x2 = tmp->wall_hit.x;
		data->y2 = tmp->wall_hit.y;
		data->ply->color = ft_rgb(30, X__COLOR);
		dda_function(
			data
		);
		tmp = tmp->next;
	}
	return (0);
}