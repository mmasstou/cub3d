/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellakr <abellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 19:51:57 by abellakr          #+#    #+#             */
/*   Updated: 2022/08/31 18:30:04 by abellakr         ###   ########.fr       */
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
	data->ply->move_speed = 0.1;
	data->ply->rotation_speed = degreeto_radian(3);
}
//---------------------------------------------------- draw fieald of view 
void	draw__fov(t_data *data)
{
	t_rays *tmp;
	
	tmp = data->rays;
	translation_player(data);
	while(tmp)
	{
		data->x1 = data->x_translation;
		data->y1 = data->y_translation;
		translation_fov(data, tmp->wall_hit.x, tmp->wall_hit.y);
		data->x2 = data->x_fov;
		data->y2 = data->y_fov;
		//color
		data->ply->color = PURPLE;
		draw_line(data, data->x_translation, data->y_translation, data->x_fov, data->y_fov);
		// dda_function(data);
		tmp = tmp->next;
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
	if(wall_collaction(newPlayerx, newPlayery, *data) == 0)
	{
		(*data)->ply->x_pos = newPlayerx;
		(*data)->ply->y_pos = newPlayery;
	}
}
//--------------------------------------------------------------------------------------------------
void    dda_function(t_data *vars) // not used for now use it later
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
        if(sqrt(pow(vars->x1 - vars->centre, 2) + pow(vars->y1 - vars->centre, 2)) < RADIUS)
			my_mlx_pixel_put(vars->x1 , vars->y1 , vars, vars->ply->color);
        vars->x1 += dx;
        vars->y1 += dy;
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
//------------------------------------------- translation fov
void translation_fov(t_data *data, float x, float y)
{
	data->k_x = data->ply->x_pos * data->unit - data->centre;
	data->k_y = data->ply->y_pos * data->unit - data->centre;
	if(data->k_x == 0)
		data->x_fov = x;
	else if(data->k_x > 0)
		data->x_fov = x - fabs(data->k_x);
	else if(data->k_x < 0)
		data->x_fov = x + fabs(data->k_x);
	if(data->k_y == 0)
		data->y_fov = y;
	else if(data->k_y < 0)
		data->y_fov = y + fabs(data->k_y);
	else if(data->k_y > 0)
		data->y_fov = y - fabs(data->k_y);
}