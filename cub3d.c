/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellakr <abellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 11:20:48 by mmasstou          #+#    #+#             */
/*   Updated: 2022/08/08 09:40:59 by abellakr         ###   ########.fr       */
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
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	(void)argc;
	// atexit(checkleaks);
	checkargs(argc, argv);
	init_data(&data);
	parsing(argv, &data);
	graphic(&data);
	return (0);
}
