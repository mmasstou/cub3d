/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 11:24:35 by mmasstou          #+#    #+#             */
/*   Updated: 2022/08/26 15:34:26 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	stock_minimap(char **minimap, t_data **data, int minimap_size)
{
	int	index;
	char *str;

	(*data)->map = (char **)malloc(sizeof(char *) * minimap_size + 1);
	if (!(*data)->map)
		_error("malloc");
	index = 0;
	while (minimap[index])
	{
		str = ft_strtrim(minimap[index], "\n");
		str = ft_strjoin(str, " ");
		(*data)->map[index] = ft_strdup(str);
		free(str);
		index++;
	}
	(*data)->map[index] = NULL;
	(*data)->h = index;
}
