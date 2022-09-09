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
	data->player = (t_player *)malloc(sizeof(t_player));
	if (!data->player)
		_error("can't malloc");
	data->map = NULL;
	data->start_map = 0;
	data->params = 0;
	data->player->walk_direction.x = 0;
	data->exit.no = 0;
	data->exit.so = 0;
	data->exit.we = 0;
	data->exit.ea = 0;
	data->exit.f = 0;
	data->exit.c = 0;
	data->nbr_rays = W / WALL_STRIPE_WITH;
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	checkargs(argc, argv);
	init_data(&data);
	parsing(argv, &data);
	init_player(&(data.player));
	data.unit = 22;
	draw__(&data);
	atexit(checkleaks);
	return (0);
}
