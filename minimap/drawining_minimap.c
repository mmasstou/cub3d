/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawining_minimap.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:55:42 by mmasstou          #+#    #+#             */
/*   Updated: 2022/08/18 04:56:35 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#define TITLE_SIZE 32
#define MAP_MUN_ROWS 0
#define MAP_MUN_ROWS 0

void    draw_rect(float x, float y, t_data *data, int color, int type)
{
	int index;
	int jndex;
	int i;
	int j;
	
	index = (x + data->unit);
	i = (y + data->unit); 
	j = y;
	while (x <= index - type)
	{
		jndex = i;
		y = j;
		while (y <= jndex - type)
		{
			my_mlx_pixel_put(x, y, data, color);
			y++;
		}
		x++;
	}
}


int	drawing_minimap(t_data	*data){
	
	int index = 0;
	int jndex = 0;
	float unitx;
	float unity;
	int rect_color;
	int i;
	data->unit = 36;
	data->ply->radius = data->unit  / 4 ;
    draw_ceilling_floor(data);
	while (data->map[index])
	{
		jndex = 0;
		while (data->map[index][jndex])
		{
			i = 0;
			unitx = jndex * data->unit;
			unity = index * data->unit;
			if (data->map[index][jndex] != ' ')
			{
				if (data->map[index][jndex] == '1')
				{
					i = 2;
					rect_color = WALL;
					draw_rect(unitx, unity, data, rect_color, i);
				}
				else if (ft_strchr("SNWE", data->map[index][jndex]) != NULL)
				{
					data->ply->spawning_orientation = data->map[index][jndex];
					data->ply->x_pos = index + data->ply->x_pos_o;
					data->ply->y_pos = jndex + data->ply->y_pos_o;
				}
			}
			jndex++;
		}
		index++;
	}
	drawing_player(data);
	return (0);
}