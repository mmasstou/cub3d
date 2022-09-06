/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_minimap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 11:24:27 by mmasstou          #+#    #+#             */
/*   Updated: 2022/08/26 15:34:26 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	parsing_minimap(char **minimap, t_data *data)
{
	char	*tmp;

	data->player->orientation = 0;
	while (minimap[data->start_map])
	{
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
