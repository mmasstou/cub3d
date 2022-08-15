/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellakr <abellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 18:39:23 by mmasstou          #+#    #+#             */
/*   Updated: 2022/08/12 16:33:25 by abellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_2d(char **map)
{
	int	index;

	index = 0;
	while (map[index])
	{
		free(map[index]);
		index++;
	}
	free(map);
}

void	parsing(char *argv[], t_data *data)
{
	char	**g_map;

	g_map = get_g_map(argv[1]);
	get_map_parameters(g_map, data);
	parsing_minimap(g_map, data);
	free_2d(g_map);
}
