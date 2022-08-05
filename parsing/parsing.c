/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 18:39:23 by mmasstou          #+#    #+#             */
/*   Updated: 2022/08/05 12:02:11 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	*ft_reassign(void *oldptr, void *newptr)
{
	free(oldptr);
	return (newptr);
}

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
	parsing_minimap(g_map, data);
	free_2d(data->map);
	free_2d(g_map);
}
