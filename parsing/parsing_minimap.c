/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_minimap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 11:24:27 by mmasstou          #+#    #+#             */
/*   Updated: 2022/08/05 11:59:13 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	parsing_minimap(char **minimap, t_data *data)
{
	int		jndex;
	char	*tmp;

	data->p = 0;
	while (minimap[data->start_map])
	{
		jndex = 0;
		tmp = ft_strtrim(minimap[data->start_map], " ");
		if (tmp[0] == '\n')
		{
			free(tmp);
			data->start_map++;
		}
		else
		{
			free(tmp);
			break ;
		}
	}
	check_minimap(&minimap[data->start_map], data);
}
