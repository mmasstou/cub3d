/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 16:51:54 by abellakr          #+#    #+#             */
/*   Updated: 2022/08/21 16:16:59 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d.h"

void	player_updata(t_data *data){
	
	(void)data;
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
	player_updata(data);
	data->ply->x_pos *= data->unit;
	data->ply->y_pos *= data->unit;
	data->ply->color = 13728527;
	draw_ply(data->ply->x_pos, data->ply->y_pos, data, WALL);
	data->ply->color = PLAYER;
	// printf("player with :%f\n", (data->ply->ply_w) / 2);
	data->ply->x_pos += data->ply->ply_w / 2;
	data->ply->y_pos += data->ply->ply_w / 2;
	draw_line(
		data,
		data->ply->x_pos,
		data->ply->y_pos,
		data->ply->x_pos + 60 * cos(data->ply->rotation_angle),
		data->ply->y_pos + 60 * sin(data->ply->rotation_angle)
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
	index = (x + 4);
	data->ply->ply_w = 0;
	i = (y + 4);
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
		data->ply->ply_w ++;
	}
}
