/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellakr <abellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 18:29:12 by abellakr          #+#    #+#             */
/*   Updated: 2022/08/29 04:45:31 by abellakr         ###   ########.fr       */
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
	init_player(&data);
	draw__(&data);
	atexit(checkleaks);
	return (0);
}