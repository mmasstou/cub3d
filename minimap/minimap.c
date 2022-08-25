/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellakr <abellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 16:51:54 by abellakr          #+#    #+#             */
/*   Updated: 2022/08/23 15:57:36 by abellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d.h"

void	player_updata(t_data **data){
	float step;

	step = (*data)->ply->walk_direction * (*data)->ply->move_speed;
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
	int x1, y1;
	// player_updata(&data);
	printf(" OLD player Pos %f, %f\n", data->ply->x_pos, data->ply->y_pos);

	x1 = data->ply->x_pos * data->unit;
	y1 = data->ply->y_pos * data->unit;
	printf("player Pos %f, %f\n", data->ply->x_pos, data->ply->y_pos);

	data->ply->color = 13728527;
	draw_ply(
		x1,
		y1, 
		data, 
		WALL);
	data->ply->color = 13728527;
	// printf("player with :%f\n", (data->ply->ply_w) / 2);
	x1 += data->ply->ply_w / 2;
	y1 += data->ply->ply_w / 2;
	field_of_views(x1, y1, data);
	data->ply->color = WALL;
	draw_line(
		data,
		x1,
		y1,
		x1 + (90 * cos(data->ply->rotation_angle)),
		y1 + (90 * sin(data->ply->rotation_angle))
	);
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
