/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 18:35:42 by mmasstou          #+#    #+#             */
/*   Updated: 2022/09/02 15:53:35 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double degreeto_radian(float angle){
	return (angle *  (M_PI / 180));
}

int ft_rgb(int t, int r, int g, int b)
{
    return ((((t * 255) / 100) << 24) | (r << 16) | (g << 8) | b);
}

void	init_player(t_player **p)
{
	(*p)->turn_direction = 0;
	(*p)->walk_direction.x = 0;
	(*p)->walk_direction.y = 0;
	if ((*p)->orientation == 'N')
		(*p)->rotation_angle = 3 * M_PI_2;
	else if ((*p)->orientation == 'S')
		(*p)->rotation_angle = M_PI_2;
	else if ((*p)->orientation == 'E')
		(*p)->rotation_angle = 0;
	else if ((*p)->orientation == 'W')
		(*p)->rotation_angle = M_PI;
	(*p)->move_speed = 0.090641;
	printf("(*p)->player %c\n", (*p)->orientation);
	(*p)->rotation_speed = degreeto_radian(1.5);
}
// void    draw__ray(t_data *vars)
// {
//     float    steps;
//     float    dx;
//     float    dy;

//     dx = vars->x2 - vars->x1;
//     dy = vars->y2 - vars->y1;
//     if (fabsf(dx) > fabsf(dy))
//         steps = fabsf(dx);
//     else
//         steps = fabsf(dy);
//     dx /= steps;
//     dy /= steps;
//     while ((int)(vars->x1 - vars->x2) || (int)(vars->y1 - vars->y2))
//     {
//         my_mlx_pixel_put(vars->x1 , vars->y1 , vars, vars->player->color);
//         vars->x1 += dx;
//         vars->y1 += dy;
// 		if (wall_collaction(vars->x1 / vars->unit , vars->y1 / vars->unit, vars) == 1)
// 			break;
//     }
// }

// void	draw__raycast(t_data *data, double x1, double y1,  double x2, double y2){
// 	data->x1 = x1;
// 	data->y1 = y1;
// 	data->x2 = x2;
// 	data->y2 = y2;
// 	dda_function(
// 		data
// 	);
// }

// void	draw__pov(t_data *data){
// 	int x1, y1;

// 	x1 = data->player->pos.x * data->unit;
// 	y1 = data->player->pos.y * data->unit;
// 	data->x1 = x1;
// 	data->y1 = y1;
// 	data->x2 = x1 + (50 * cos(data->player->rotation_angle));
// 	data->y2 = y1 + (50 * sin(data->player->rotation_angle));
// 	data->player->color = ft_rgb(30, 255,0,0);
// 	dda_function(
// 		data
// 	);
// }

// void	draw__player(t_data *data){
// 	int x1, y1;
// 	player_update(&data);
// 	x1 = data->player->pos.x * data->unit;
// 	y1 = data->player->pos.y * data->unit;
// 	render_player(
// 		data, 
// 		x1,
// 		y1, 
// 		WALL
// 		);
// }

// void	render_player(t_data *data, float x, float y, int color){
// 	float i;
// 	float j;
// 	int unit;
// 	int unity;

// 	unit = 1;
// 	i = x + unit;
// 	j = y + unit;
// 	unity = y;
// 	while (x <= i)
// 	{
// 		y = unity;
// 		while (y <= j)
// 		{
// 			my_mlx_pixel_put(x, y, data, color);
// 			y++;
// 		}
// 		x++;
// 	}
// }

void	player_update(t_data **data){
	float step;
	float newPlayerx;
	float newPlayery;

	// move right and left
	step = (*data)->player->walk_direction.x * (*data)->player->move_speed;
	newPlayerx = (*data)->player->pos.x - (sin((*data)->player->rotation_angle) * step);
	newPlayery = (*data)->player->pos.y + (cos((*data)->player->rotation_angle) * step);
	if (wall_collaction(newPlayerx, newPlayery, *data) == 0)
	{
		(*data)->player->pos.x = newPlayerx;
		(*data)->player->pos.y = newPlayery;
	}
	// move up and down
	step = (*data)->player->walk_direction.y * (*data)->player->move_speed;
	(*data)->player->rotation_angle += ((*data)->player->turn_direction * (*data)->player->rotation_speed);
	normalize_angle(&((*data)->player->rotation_angle));
	newPlayerx = (*data)->player->pos.x + (cos((*data)->player->rotation_angle) * step);
	newPlayery = (*data)->player->pos.y + (sin((*data)->player->rotation_angle) * step);
	if (wall_collaction(newPlayerx, newPlayery, *data) == 0)
	{
		(*data)->player->pos.x = newPlayerx;
		(*data)->player->pos.y = newPlayery;
	}
}

// void    dda_function(t_data *vars)
// {
//     double    steps;
//     double    dx;
//     double    dy;

//     dx = vars->x2 - vars->x1;
//     dy = vars->y2 - vars->y1;
//     if (fabs(dx) > fabs(dy))
//         steps = fabs(dx);
//     else
//         steps = fabs(dy);
//     dx /= steps;
//     dy /= steps;
//     while ((int)(vars->x1 - vars->x2) || (int)(vars->y1 - vars->y2))
//     {
//         my_mlx_pixel_put(vars->x1 , vars->y1 , vars, vars->player->color);
//         vars->x1 += dx;
//         vars->y1 += dy;
// 		// if (wall_collaction(vars->x1 / vars->unit , vars->y1 / vars->unit, vars) == 1)
// 		// 	break;
//     }
// }