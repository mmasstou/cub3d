/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 11:24:12 by mmasstou          #+#    #+#             */
/*   Updated: 2022/09/02 10:20:22 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	check_player_and_zero(
	t_data *data, char **minimap, int index, int jndex)
{
	if (ft_strchr("SNWE", minimap[index][jndex]) != NULL)
	{
		data->player->pos.x = jndex + 0.5;
		data->player->pos.y = index + 0.5;
	}
	chech_direction(minimap, index - 1, jndex);
	chech_direction(minimap, index + 1, jndex);
	chech_direction(minimap, index, jndex - 1);
	chech_direction(minimap, index, jndex + 1);
}

void	check_minimap(char **map, t_data *data)
{
	int	index;
	int	jndex;
	int	end_map;

	index = -1;
	end_map = 0;
	while (map[++index])
	{
		jndex = -1;
		map[index] = ft_reassign(map[index], ft_strtrim(map[index], "\n"));
		if (!map[index] ||( map[index] &&  map[index][0] == '\0'))
			end_map = index;
		else if ((map[index] || map[index][0] == '\0' ) && end_map != 0)
			_error("empty Line in Map");
		while (map[index] && map[index][++jndex] != '\0')
		{
			if (map[index][jndex] == SPACE || map[index][jndex] == ONE)
				continue ;
			else if (map[index][jndex] == ZERO || \
			is_player(map[index][jndex], data) == true)
				check_player_and_zero(data, map, index, jndex);
			else
				_error("Stranger Element");
		}
	}
	if (data->player->orientation == 0)
		_error("No player in Map");
	stock_minimap(map, &data, end_map);
}
