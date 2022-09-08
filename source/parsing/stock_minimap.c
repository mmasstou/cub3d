/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 11:24:35 by mmasstou          #+#    #+#             */
/*   Updated: 2022/08/30 12:48:57 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	stock_minimap(char **map, t_data **data, int minimap_size)
{
	int	index;

	(*data)->map = (char **)malloc(sizeof(char *) * minimap_size + 1);
	if (!(*data)->map)
		_error("malloc");
	index = 0;
	while (map[index] && map[index][0] != '\0')
	{
		map[index] = ft_reassign(map[index], ft_strjoin(map[index], " "));
		(*data)->map[index] = ft_strdup(map[index]);
		index++;
	}
	(*data)->map[index] = NULL;
}
