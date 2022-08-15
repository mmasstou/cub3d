/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 11:24:35 by mmasstou          #+#    #+#             */
/*   Updated: 2022/08/14 14:55:59 by mmasstou         ###   ########.fr       */
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
	(*data)->h = index;
}
