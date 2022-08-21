/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 16:51:54 by abellakr          #+#    #+#             */
/*   Updated: 2022/08/21 14:07:32 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d.h"

void	player_updata(t_data *data){
	(void)data;
	return ;
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
		my_mlx_pixel_put(x,y,data,13728527);
		e2 = 2*err;
		if (e2 >= dy) { /* e_xy+e_x > 0 */
 		if (x == x1) break;
 		err += dy; x += sx;
	 	}
 		if (e2 <= dx) { /* e_xy+e_y < 0 */
 		if (y == y1) break;
 		err += dx; y += sy;
 		}
	}
}

void	player_render(t_data *data){
	double angle;
	double x;
	double y;
	data->ply->color = 13728527;
	data->ply->x_pos *= data->unit;
	data->ply->y_pos *= data->unit;
	draw_ply(
		data->ply->x_pos,
		data->ply->y_pos,
		data,
		WALL
	);
	data->ply->color = 13728527;
	angle = M_PI / 2;
	x = data->ply->x_pos + 30 *cos(angle);
	y = data->ply->y_pos + 30 *sin(angle);
	draw_line(
		data,
		data->ply->x_pos,
		data->ply->y_pos,
		x,
		y
	);
}

void    draw_ply(float x, float y, t_data *data, int color)
{
	int index;
	int jndex;
	int next_x;
	int next_y;
	int i;
	int j;
	int unitx;
	int unity;

	(void)color;
	unitx = x;
	unity = y;
	index = (x + data->unit / 4);
	data->ply->ply_w = index;
	i = (y + data->unit / 4);
	j = y;
	while (x <= index)
	{
		jndex = i;
		y = j;
		while (y <= jndex)
		{
			if (x < index)
			{
				next_x = x + 1;
				row_dda(x, y, next_x, next_y, data);
			}
			if (y < jndex)
			{
				next_y = y + 1;
				row_dda(x, y, next_x, next_y, data);
			}
			y++;
		}
		x++;
	}
}
