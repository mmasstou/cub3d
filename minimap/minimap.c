/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 16:51:54 by abellakr          #+#    #+#             */
/*   Updated: 2022/08/21 13:17:38 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d.h"

void	player_updata(t_data *data){
	(void)data;
	return ;
}

void	player_render(t_data *data){
	double angle;
	data->ply->color = 13728527;
	data->ply->x_pos *= data->unit;
	data->ply->y_pos *= data->unit;
	draw_ply(
		data->ply->x_pos,
		data->ply->y_pos,
		data,
		WALL
	);
	angle = 0.0;
	row_dda(
		data->ply->x_pos,
		data->ply->y_pos,
		data->ply->x_pos + cos(angle + M_PI_4) * 30,
		data->ply->y_pos + sin(angle + M_PI_4) * 30,
		data
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
