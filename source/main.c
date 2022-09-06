/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 18:35:33 by mmasstou          #+#    #+#             */
/*   Updated: 2022/09/02 16:52:07 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	checkleaks(void)
{
	printf("\033[0;31m----------------------------\n");
	system("leaks cub3D");
	printf("\n----------------------------\n\033[0m");
}

int	init_data(t_data *data)
{
	data->ply = (t_player *)malloc(sizeof(t_player));
	if (!data->ply)
		_error("can't malloc");
	data->map = NULL;
	data->start_map = 0;
	data->params = 0;
	data->p = 0;
	data->mm = 0;
	data->exit.no = 0;
	data->exit.so = 0;
	data->exit.we = 0;
	data->exit.ea = 0;
	data->exit.f = 0;
	data->exit.c = 0;
	data->last_x = 0;
	data->last_y = 0;
	data->bita = 0;
	data->p_up = 0;
	data->angle_ea = 0;
	data->angle_no = 3 * M_PI_2;
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;
	int i = 0,j = 0;

	checkargs(argc, argv);
	init_data(&data);
	parsing(argv, &data);
	while (data.map[i])
	{
		j = 0;
		while (data.map[i][j])
		{
			if (ft_strchr("SNWE", data.map[i][j]) != NULL)
			{
				data.ply->x_pos = j + 0.5;
				data.ply->y_pos = i + 0.5;
			}
			j++;
		}
		i++;
	}
	data.map_size.x = j;
	data.map_size.x = i;
	init_player(&(data.ply));
	j = (W > H) ? H: W;
	i = (data.map_coords.x > data.map_coords.y) ? data.map_coords.x: data.map_coords.y;
	j /= i;
	// data.unit = j > 20 ? 22 : j;
	data.unit = 22;
	draw__(&data);
	atexit(checkleaks);
	return (0);
}
