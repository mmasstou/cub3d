/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellakr <abellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 19:51:57 by abellakr          #+#    #+#             */
/*   Updated: 2022/08/30 18:45:00 by abellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//----------------------------------------- degree to radian function
double degreeto_radian(float angle){
	return (angle *  (M_PI / 180));
}
//-------------------------------------------- rgb function
int ft_rgb(int t, int r, int g, int b)
{
    return ((((t * 255) / 100) << 24) + (r << 16) + (g << 8) + b);
}
//-------------------------------------------------- init player
void	init_player(t_data *data)
{
	int i = 0,j = 0;
	data->ply = (t_player *)malloc(sizeof(t_player));
	if (!data->ply)
		_error("can't malloc");
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (ft_strchr("SNWE", data->map[i][j]) != NULL)
			{
				data->ply->x_pos = j;
				data->ply->y_pos = i;
				data->ply->spawning_orientation = data->map[i][j];
			}
			j++;
		}
		i++;
	}
	data->ply->x_pos_o = 0;
	data->ply->y_pos_o = 0;
	data->ply->radius = 0;
	data->ply->turn_direction = 0;
	data->ply->walk_direction = 0;
	// printf("player orientation +> %c\n", data->ply->spawning_orientation);
	if (data->ply->spawning_orientation == 'N')
		data->ply->rotation_angle = 3 * M_PI_2;
	else if (data->ply->spawning_orientation == 'S')
		data->ply->rotation_angle = M_PI_2;
	else if (data->ply->spawning_orientation == 'E')
		data->ply->rotation_angle = 0;
	else if (data->ply->spawning_orientation == 'W')
		data->ply->rotation_angle = M_PI;
	data->ply->move_speed = 0.05;
	data->ply->rotation_speed = degreeto_radian(1.5);
}
//-------------------------------------------- dda
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
        vars->x1_map += dx;
        vars->y1_map += dy;
        vars->x1 += dx;
        vars->y1 += dy;
		if (wall_collaction(vars->x1_map / vars->unit, vars->y1_map / vars->unit, vars) == 1)
			break;
    }
}
//---------------------------------------------------- draw fieald of view 
void	draw__fov(t_data *data){
	int index;
	float win_palyer__x;
	float win_palyer__y;
	double	ray__angle;
	float win_palyer__x_map;
	float win_palyer__y_map;

	win_palyer__x = data->x_translation;
	win_palyer__y = data->y_translation;
	//---------------------------
	win_palyer__x_map = data->ply->x_pos * data->unit;
	win_palyer__y_map = data->ply->y_pos * data->unit;
	//---------------------------------------
	ray__angle = data->ply->rotation_angle - degreeto_radian(FOV) / 2;
	index = 0;
	while (index < NBR_RAYS){
		// start
		data->x1 = win_palyer__x;
		data->y1 = win_palyer__y;
		data->x1_map = win_palyer__x_map;
		data->y1_map = win_palyer__y_map;
		// end 
		data->x2 = win_palyer__x + (80 * cos(ray__angle));
		data->y2 = win_palyer__y + (80 * sin(ray__angle));
		//color
		data->ply->color = ft_rgb(15, FOV_COLOR);
		// translation fov
		draw__ray(data);
		ray__angle += degreeto_radian(FOV) / NBR_RAYS;
		index ++;
	}


}
//----------------------------------------------
void	draw__pov(t_data *data){
	int x1, y1;

	x1 = data->x_translation;
	y1 = data->y_translation;
	data->x1 = x1;
	data->y1 = y1;
	data->x2 = x1 + (20 * cos(data->ply->rotation_angle));
	data->y2 = y1 + (20 * sin(data->ply->rotation_angle));
	data->ply->color = ft_rgb(30, FOV_COLOR);
	dda_function(data);
}
//------------------------------------------------
void	draw__player(t_data *data){
	player_update(&data);
	translation_player(data);
	// render_player(data, data->x_translation,data->y_translation, PURPLE);
}
//--------------------------------------------------------------------------------------
void	render_player(t_data *data, float x, float y, int color){
	float i;
	float j;
	int unit;
	int unity;

	unit = 2;
	i = x + unit;
	j = y + unit;
	unity = y;
	while (x <= i)
	{
		y = unity;
		while (y <= j)
		{
            if(sqrt(pow(x - data->centre, 2) + pow(y - data->centre, 2)) < RADIUS)	
				my_mlx_pixel_put(x, y, data, color);
			y++;
		}
		x++;
	}
}
//----------------------------------------------------------------------------
void	player_update(t_data **data){
	float step;
	float newPlayerx;
	float newPlayery;

	// move right and left
	step = (*data)->mm * (*data)->ply->move_speed;
	newPlayerx = (*data)->ply->x_pos - (sin((*data)->ply->rotation_angle) * step);
	newPlayery = (*data)->ply->y_pos + (cos((*data)->ply->rotation_angle) * step);
	if (wall_collaction(newPlayerx, newPlayery, *data) != 1)
	{
		(*data)->ply->x_pos = newPlayerx;
		(*data)->ply->y_pos = newPlayery;
	}
	// move up and down
	step = (*data)->ply->walk_direction * (*data)->ply->move_speed;
	(*data)->ply->rotation_angle += ((*data)->ply->turn_direction * (*data)->ply->rotation_speed);
	newPlayerx = (*data)->ply->x_pos + (cos((*data)->ply->rotation_angle) * step);
	newPlayery = (*data)->ply->y_pos + (sin((*data)->ply->rotation_angle) * step);
	if (wall_collaction(newPlayerx, newPlayery, *data) != 1)
	{
		(*data)->ply->x_pos = newPlayerx;
		(*data)->ply->y_pos = newPlayery;
	}
}
//--------------------------------------------------------------------------------------------------
void    dda_function(t_data *vars)
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
//------------------------------------------- translation player 
void	translation_player(t_data *data)
{
	data->k_x = data->ply->x_pos * data->unit - data->centre;
	data->k_y = data->ply->y_pos * data->unit - data->centre;
	if(data->k_x == 0)
		data->x_translation = data->ply->x_pos * data->unit;
	else if(data->k_x > 0)
		data->x_translation = data->ply->x_pos * data->unit - fabs(data->k_x);
	else if(data->k_x < 0)
		data->x_translation = data->ply->x_pos * data->unit + fabs(data->k_x);
	if(data->k_y == 0)
		data->y_translation = data->ply->y_pos * data->unit;
	else if(data->k_y < 0)
		data->y_translation = (data->ply->y_pos * data->unit) + fabs(data->k_y);
	else if(data->k_y > 0)
		data->y_translation = (data->ply->y_pos * data->unit) - fabs(data->k_y);
}