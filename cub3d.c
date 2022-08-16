/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 11:20:48 by mmasstou          #+#    #+#             */
/*   Updated: 2022/08/16 15:16:57 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	checkleaks(void)
{
	printf("\033[0;31m----------------------------\n");
	system("leaks cub3D");
	printf("\n----------------------------\n\033[0m");
}

int	init_data(t_data *data)
{
	data->map = NULL;
	data->start_map = 0;
	data->params = 0;
	data->p = 0;
	data->exit.no = 0;
	data->exit.so = 0;
	data->exit.we = 0;
	data->exit.ea = 0;
	data->exit.f = 0;
	data->exit.c = 0;
	data->unit = 34;
	data->last_x = 0;
	data->last_y = 0;
	data->bita = 0;
	data->p_up = 0;
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	checkargs(argc, argv);
	init_data(&data);
	parsing(argv, &data);
	graphic(&data);
	// free_params(&data);
	// free_array(data.map);
	atexit(checkleaks);
	return (0);
}
