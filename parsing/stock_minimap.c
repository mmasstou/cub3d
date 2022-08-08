/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellakr <abellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 11:24:35 by mmasstou          #+#    #+#             */
/*   Updated: 2022/08/08 09:39:23 by abellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	stock_minimap(char **minimap, t_data **data, int minimap_size)
{
	int	index;

	(*data)->map = (char **)malloc(sizeof(char *) * minimap_size + 1);
	if (!(*data)->map)
		_error("malloc");
	index = 0;
	while (minimap[index])
	{
		(*data)->map[index] = ft_strdup(minimap[index]);
		index++;
	}
	(*data)->map[index] = NULL;
}
