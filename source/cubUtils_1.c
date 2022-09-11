/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubUtils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 13:14:24 by mmasstou          #+#    #+#             */
/*   Updated: 2022/09/11 13:16:05 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	wall_collaction(float index, float jndex, t_data *data)
{
	int	x;
	int	y;
	int	array_len;
	int	str_len;

	array_len = ft_arraylen(data->map);
	x = floor(index);
	y = floor(jndex);
	if (y > array_len || y < 0)
		return (1);
	if (y >= 0 && data->map[y] != NULL)
	{
		str_len = ft_strlen(data->map[y]);
		if (x > str_len || x < 0)
			return (1);
		if (data->map[y][x] == '1' || data->map[y][x] == ' ')
			return (1);
		else if (data->map[y][x] == '0' || \
		ft_strchr("SWNE", data->map[y][x]) != NULL)
			return (0);
	}
	return (0);
}

void	checkargs(int argc, char *argv[])
{
	char	*map_name;
	int		fd;

	if (argc != 2)
		_error("argument required");
	map_name = ft_strrchr(argv[1], '.');
	if ((map_name && ft_strcmp(map_name, ".cub") != 0) || !map_name)
	{
		_error("Map in format *.cub required ");
	}
	fd = open(argv[1], O_RDONLY, 0777);
	if (fd == -1)
		_error("Can`t Open Map");
	else
		close(fd);
}
