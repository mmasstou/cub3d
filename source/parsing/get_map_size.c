/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 11:24:18 by mmasstou          #+#    #+#             */
/*   Updated: 2022/08/26 15:34:26 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	get_map_size(char *file)
{
	int		index;
	int		fd;
	char	*line;

	index = 1;
	fd = open(file, O_RDONLY, 0777);
	if (fd == -1)
		exit (1);
	line = get_next_line(fd);
	if (line == NULL)
		_error("Map Not found");
	while (line)
	{
		index++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (index + 1);
}
