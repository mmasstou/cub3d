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

void	is_empty_line(char *line, int *end_map, int index)
{
	char	*str;

	str = ft_strtrim(line, " ");
	if ((!str || str[0] != '\0') && *end_map != 0)
	{
		if (line != NULL)
			_error("Empty Line in Map");
	}
	else if ((!str || str[0] == '\0') && *end_map == 0)
		*end_map = index;
	free(str);
}

int	is_element_in_map(
	t_data *data, char **map, int index, int jndex)
{
	int	ret;

	ret = 0;
	if (map[index][jndex] == SPACE)
		ret = 1;
	else if (map[index][jndex] == ONE)
		ret = 1;
	else if (map[index][jndex] == ZERO )
	{
		check_player_and_zero(data, map, index, jndex);
		ret = 1;
	}
	else if (is_player(map[index][jndex], data))
	{
		check_player_and_zero(data, map, index, jndex);
		ret = 1;
	}
	return (ret);
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
		// map[index] = ft_reassign(map[index], ft_strtrim(map[index], "\n"));
		map[index] = ft_strtrim(map[index], "\n");
		is_empty_line(map[index], &end_map, index);
		while (map[index] && map[index][++jndex] != '\0')
		{
			if (is_element_in_map(data, map, index, jndex))
				continue;
			else
				_error("Strange Element");
		}
	}
	if (data->player->orientation == 0)
		_error("No player in Map");
	stock_minimap(map, &data, end_map);
}
