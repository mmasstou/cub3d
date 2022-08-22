/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellakr <abellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 16:51:54 by abellakr          #+#    #+#             */
/*   Updated: 2022/08/22 10:09:03 by abellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d.h"

void	player_updata(t_data **data){
	float step;

	step = (*data)->ply->walk_direction * (*data)->ply->move_speed;
	// (*data)->ply->rotation_angle += ((*data)->ply->turn_direction * (*data)->ply->rotation_speed);
	// (*data)->ply->x_pos += (step * cos((*data)->ply->rotation_angle));
	// (*data)->ply->y_pos += (step * sin((*data)->ply->rotation_angle));
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
	player_updata(&data);
	data->ply->x_pos *= data->unit;
	data->ply->y_pos *= data->unit;
	data->ply->color = 13728527;
	draw_ply(
		data->ply->x_pos,
		data->ply->y_pos, 
		data, 
		WALL);
	data->ply->color = 13728527;
	// printf("player with :%f\n", (data->ply->ply_w) / 2);
	data->ply->x_pos += data->ply->ply_w / 2;
	data->ply->y_pos += data->ply->ply_w / 2;
	field_of_views(data);
	data->ply->color = WALL;
	// draw_line(
	// 	data,
	// 	data->ply->x_pos,
	// 	data->ply->y_pos,
	// 	data->ply->x_pos + (90 * cos(data->ply->rotation_angle)),
	// 	data->ply->y_pos + (90 * sin(data->ply->rotation_angle))
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

	unit = data->unit / 5;
	i = x + unit;
	j = y + unit;
	x -= unit / 2;
	y -= unit / 2;
	unity = y;
	while (x <= i - unit / 2)
	{
		y = unity;
		while (y <= j - unit / 2)
		{
			my_mlx_pixel_put(x, y, data, color);
			y++;
		}
		x++;
	}
}
