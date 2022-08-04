/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellakr <abellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 18:39:23 by mmasstou          #+#    #+#             */
/*   Updated: 2022/08/04 15:05:11 by abellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
//---------------------------------------------- function to get map size
int get_map_size(char *file)
{
	int index;
	int fd;
	char    *line;

	index = 0;
	fd = open(file, O_RDONLY, 0777);
	if (fd == -1)
		exit (1);
	line = get_next_line(fd);
	if(line == NULL)
		ft_error();
	while (line)
	{
		index++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (index);
}
//------------------------------------------------------ function to get all map 
char    **get_g_map(char *file, int *g_map_size)
{
	int     fd;
	char    **g_map;
	char    *line;
	int     index;

	(*g_map_size) = get_map_size(file);
	g_map = (char **)malloc(sizeof(char *) * (*g_map_size) + 1);
	if (!g_map)
		exit(1);
	fd = open(file, O_RDONLY, 0777);
	if (fd == -1)
		exit (1);
	line = get_next_line(fd);
	index = 0;
	while (line)
	{
		g_map[index] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
		index++;
	}
	return (g_map[index] = NULL, g_map);
}
//---------------------------------------------------------- parsing 
void    parsing(char *argv[], t_data *data)
{
	char    **g_map;
	int     g_map_size;
	int     index;

	g_map = get_g_map(argv[1], &g_map_size);
	get_map_parameters(g_map, data);
	index = 0;
	while (g_map[index])
	{
		free(g_map[index]);
		index++;
	}
	free(g_map);
}

