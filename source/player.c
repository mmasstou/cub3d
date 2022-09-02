/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 18:35:42 by mmasstou          #+#    #+#             */
/*   Updated: 2022/09/02 12:30:24 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double degreeto_radian(float angle){
	return (angle *  (M_PI / 180));
}

int ft_rgb(int t, int r, int g, int b)
{
    return ((t << 24) | (r << 16) | (g << 8) | b);
}

void	init_player(t_player **p){
	(*p)->win_middle_width = W / 2;
	(*p)->mouse_clik = 0;
	(*p)->x_pos_o = 0;
	(*p)->y_pos_o = 0;
	(*p)->radius = 0;
	(*p)->turn_direction = 0;
	(*p)->walk_direction = 0;
	if ((*p)->spawning_orientation == 'N')
		(*p)->rotation_angle = 3 * M_PI_2;
	else if ((*p)->spawning_orientation == 'S')
		(*p)->rotation_angle = M_PI_2;
	else if ((*p)->spawning_orientation == 'E')
		(*p)->rotation_angle = 0;
	else if ((*p)->spawning_orientation == 'W')
		(*p)->rotation_angle = M_PI;
	(*p)->move_speed = (W / cos(M_PI_4)) / 60000;
	printf("(*p)->move_speed %f\n", (*p)->move_speed);
	(*p)->rotation_speed = degreeto_radian(1.5);
}
void    draw__ray(t_data *vars)
{
    float    steps;
    float    dx;
    float    dy;

    dx = vars->x2 - vars->x1;
    dy = vars->y2 - vars->y1;
    if (fabsf(dx) > fabsf(dy))
        steps = fabsf(dx);
    else
        steps = fabsf(dy);
    dx /= steps;
    dy /= steps;
    while ((int)(vars->x1 - vars->x2) || (int)(vars->y1 - vars->y2))
    {
        my_mlx_pixel_put(vars->x1 , vars->y1 , vars, vars->ply->color);
        vars->x1 += dx;
        vars->y1 += dy;
		if (wall_collaction(vars->x1 / vars->unit , vars->y1 / vars->unit, vars) == 1)
			break;
    }
}

void	draw__raycast(t_data *data, double x1, double y1,  double x2, double y2){
	data->x1 = x1;
	data->y1 = y1;
	data->x2 = x2;
	data->y2 = y2;
	dda_function(
		data
	);
}

void	draw__pov(t_data *data){
	int x1, y1;

	x1 = data->ply->x_pos * data->unit;
	y1 = data->ply->y_pos * data->unit;
	data->x1 = x1;
	data->y1 = y1;
	data->x2 = x1 + (50 * cos(data->ply->rotation_angle));
	data->y2 = y1 + (50 * sin(data->ply->rotation_angle));
	data->ply->color = ft_rgb(30, 255,0,0);
	dda_function(
		data
	);
}

void	draw__player(t_data *data){
	int x1, y1;
	player_update(&data);
	x1 = data->ply->x_pos * data->unit;
	y1 = data->ply->y_pos * data->unit;
	render_player(
		data, 
		x1,
		y1, 
		WALL
		);
}

void	render_player(t_data *data, float x, float y, int color){
	float i;
	float j;
	int unit;
	int unity;

	unit = 1;
	// y += H  - (data->map_size.x * data->unit);
	i = x + unit;
	j = y + unit;
	unity = y;
	while (x <= i)
	{
		y = unity;
		while (y <= j)
		{
			my_mlx_pixel_put(x, y, data, color);
			y++;
		}
		x++;
	}
}

void	player_update(t_data **data){
	float step;
	float newPlayerx;
	float newPlayery;

	// move right and left
	step = (*data)->mm * (*data)->ply->move_speed;
	newPlayerx = (*data)->ply->x_pos - (sin((*data)->ply->rotation_angle) * step);
	newPlayery = (*data)->ply->y_pos + (cos((*data)->ply->rotation_angle) * step);
	if (wall_collaction(newPlayerx, newPlayery, *data) == 0)
	{
		(*data)->ply->x_pos = newPlayerx;
		(*data)->ply->y_pos = newPlayery;
	}
	// move up and down
	step = (*data)->ply->walk_direction * (*data)->ply->move_speed;
	(*data)->ply->rotation_angle += ((*data)->ply->turn_direction * (*data)->ply->rotation_speed);
	// (*data)->ply->rotation_angle += ((*data)->ply->turn_direction_mouse * (*data)->ply->rotation_speed);
	normalize_angle(&((*data)->ply->rotation_angle));
	newPlayerx = (*data)->ply->x_pos + (cos((*data)->ply->rotation_angle) * step);
	newPlayery = (*data)->ply->y_pos + (sin((*data)->ply->rotation_angle) * step);
	if (wall_collaction(newPlayerx, newPlayery, *data) == 0)
	{
		(*data)->ply->x_pos = newPlayerx;
		(*data)->ply->y_pos = newPlayery;
	}
	/*
	? test derictions 
	*/
	// bool	is_ray_facing_down = ((*data)->ply->rotation_angle > 0 && (*data)->ply->rotation_angle < M_PI);
	// bool	is_ray_facing_up = !is_ray_facing_down;
	// bool	is_ray_facing_left = ((*data)->ply->rotation_angle > M_PI_2 && (*data)->ply->rotation_angle < 3 * M_PI_2);
	// bool	is_ray_facing_right = !is_ray_facing_left;
	// if (is_ray_facing_down)
	// 	printf("ray_facing_down\n");
	// if (is_ray_facing_up)
	// 	printf("ray_facing_up\n");
	// if (is_ray_facing_left)
	// 	printf("ray_facing_left\n");
	// if (is_ray_facing_right)
	// 	printf("ray_facing_right\n");
}

void    dda_function(t_data *vars)
{
    double    steps;
    double    dx;
    double    dy;

    dx = vars->x2 - vars->x1;
    dy = vars->y2 - vars->y1;
    if (fabs(dx) > fabs(dy))
        steps = fabs(dx);
    else
        steps = fabs(dy);
    dx /= steps;
    dy /= steps;
    while ((int)(vars->x1 - vars->x2) || (int)(vars->y1 - vars->y2))
    {
        my_mlx_pixel_put(vars->x1 , vars->y1 , vars, vars->ply->color);
        vars->x1 += dx;
        vars->y1 += dy;
		// if (wall_collaction(vars->x1 / vars->unit , vars->y1 / vars->unit, vars) == 1)
		// 	break;
    }
}