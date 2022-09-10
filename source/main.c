/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellakr <abellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 18:35:33 by mmasstou          #+#    #+#             */
/*   Updated: 2022/09/10 11:08:31 by abellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	init_data(t_data *data)
{
	data->player = (t_player *)malloc(sizeof(t_player));
	if (!data->player)
		_error("can't malloc");
	data->map = NULL;
	data->start_map = 0;
	data->unit = 22;
	data->params = 0;
	data->player->walk_direction.x = 0;
	data->exit.no = 0;
	data->exit.so = 0;
	data->exit.we = 0;
	data->exit.ea = 0;
	data->exit.f = 0;
	data->exit.c = 0;
	data->nbr_rays = W / WALL_STRIPE_WITH;
	data->pressed = FALSE;
	return (0);
}

void	free_texture(t_texture *tex)
{
	t_texture	*tmp;

	while (tex)
	{
		tmp = tex->next;
		free(tex);
		tex = tmp;
	}
}

int	main(int argc, char *argv[])
{
	t_data	data;

	checkargs(argc, argv);
	init_data(&data);
	parsing(argv, &data);
	init_player(&(data.player));
	graphic(&data);
	free_params(&data);
	free_array(data.map);
	free(data.player);
	free(data.rays);
	free_texture(data.tex);
	return (0);
}
