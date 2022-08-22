/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawining_minimap.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:55:42 by mmasstou          #+#    #+#             */
/*   Updated: 2022/08/21 16:15:32 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#define TITLE_SIZE 32
#define MAP_MUN_ROWS 0
#define MAP_MUN_ROWS 0

void	my_mlx_pixel_put(int x, int y, t_data *data, int color)
{
	char	*dst;

	if ((x >= 0 && x < W) && (y >= 0 && y < H))
	{
		dst = data->mlx_vars->buffer + (y * data->mlx_vars->line_lenght + x * (data->mlx_vars->bpp / 8));
		*(unsigned int *)dst = color;
	}
}
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
	float	inc;
	float unitx;
	float unity;
	int rect_color;
	int i;
	data->unit = 36;
	data->ply->radius = data->unit  / 4 ;
    draw_ceilling_floor(data);
	inc = 0.1;
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
					data->ply->x_pos = jndex + data->ply->x_pos_o;
					data->ply->y_pos = index + data->ply->y_pos_o;
				}
			}
			jndex ++;
		}
		index ++;
	}
	
	player_render(data);
	return (0);
}