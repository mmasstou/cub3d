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

void	get_player_pos(int x, int y, t_data **data)
{
	(*data)->player->pos.x = x;
	(*data)->player->pos.y = y;
}

void	check_player_and_zero(char **minimap, int index, int jndex)
{
	chech_direction(minimap, index - 1, jndex);
	chech_direction(minimap, index + 1, jndex);
	chech_direction(minimap, index, jndex - 1);
	chech_direction(minimap, index, jndex + 1);
}

void	check_minimap(char **map, t_data *data)
{
	int	index;
	int	jndex;

	index = -1;
	while (map[++index])
	{
		jndex = -1;
		map[index] = ft_reassign(map[index], ft_strtrim(map[index], "\n"));
		while (map[index][++jndex] != '\0')
		{
			if (map[index][jndex] == SPACE || map[index][jndex] == ONE)
				continue ;
			else if (map[index][jndex] == ZERO || \
			is_player(map[index][jndex], data) == true)
				check_player_and_zero(map, index, jndex);
			else
				_error("Stranger Element");
		}
	}
	if (data->player->orientation == 0)
		_error("No player in Map");
	stock_minimap(map, &data, index + 1);
}
