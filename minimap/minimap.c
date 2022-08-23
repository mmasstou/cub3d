/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 16:51:54 by abellakr          #+#    #+#             */
/*   Updated: 2022/08/23 19:02:07 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d.h"

void	player_updata(t_data **data){
	float step;
	step = (*data)->ply->walk_direction * (*data)->ply->move_speed;
	// (*data)->ply->x_pos = (*data)->ply->x_pos + (cos((*data)->ply->rotation_angle) * step);
	// 	(*data)->ply->y_pos = (*data)->ply->y_pos + (sin((*data)->ply->rotation_angle) * step);
}
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
    }
}

void draw_line(t_data *data, int x, int y, int x1, int y1)
{
	int dx, dy, err, sx,sy,e2;

	dx = abs(x1 - x);
	dy = -abs(y1 - y);
	sx = x < x1 ? 1 : -1;
	sy = y < y1 ? 1 : -1;
	err = dx + dy;
	while (1)
	{
		my_mlx_pixel_put(x,y,data,data->ply->color);
		e2 = 2*err;
		if (e2 >= dy) 
		{ /* e_xy+e_x > 0 */
			if (x == x1) break;
			err += dy; x += sx;
	 	}
 		if (e2 <= dx) 
		{ /* e_xy+e_y < 0 */
 			if (y == y1) break;
 			err += dx; y += sy;
 		}
	}
}

void	player_render(t_data *data){
	double ray_angle;
	int x1, y1;
	player_updata(&data);
	// printf(" OLD player Pos %f, %f\n", data->ply->x_pos, data->ply->y_pos);
	x1 = data->ply->x_pos * data->unit;
	y1 = data->ply->y_pos * data->unit;
	// printf("player Pos %f, %f\n", data->ply->x_pos, data->ply->y_pos);
	data->ply->color = 13728527;
	draw_ply(
		x1,
		y1, 
		data, 
		WALL);
	data->ply->color = 13728527;
	// printf("player with :%f\n", (data->ply->ply_w) / 2);
	// x1 += data->ply->ply_w / 2;
	// y1 += data->ply->ply_w / 2;
	data->x1 = x1;
	data->y1 = y1;
	data->x2 = x1 + (90 * cos(data->ply->rotation_angle));
	data->y2 = y1 + (90 * sin(data->ply->rotation_angle));
	ray_angle = data->ply->rotation_angle - (FOV / 2);
	ray_caste(data);
	// field_of_views(x1, y1, ray_angle,  data);
	data->ply->color = WALL;
		dda_function(
		data
	);
	// draw_line(
	// 	data,
	// 	x1,
	// 	y1,
	// 	x1 + (90 * cos(data->ply->rotation_angle)),
	// 	y1 + (90 * sin(data->ply->rotation_angle))
	// );
}

void    draw_ply(float x, float y, t_data *data, int color)
{
	int index;
	int jndex;
	int next_x;
	int next_y;
	float i;
	float j;
	int unit;
	int unity;

	data->ply->ply_w = 0;
	unit = data->unit / 5;
	x -= (unit / 2);
	y -= (unit / 2);
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
		data->ply->ply_w ++;
	}
}
