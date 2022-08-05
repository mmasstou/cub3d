/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_g_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 11:24:15 by mmasstou          #+#    #+#             */
/*   Updated: 2022/08/05 11:24:16 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char    **get_g_map(char *file)
{
    int     fd;
    char    **g_map;
    char    *line;
    int     index;

    g_map = (char **)malloc(sizeof(char *) *  get_map_size(file) + 1);
    if (!g_map)
        exit(1);
    fd = open(file, O_RDONLY, 0777);
    if (fd == -1)
        exit (1);
    line = get_next_line(fd);
    if (!line)
        _error("Map Not found");
    index = 0;
    while (line)
    {
        g_map[index] = ft_strdup(line);
        free(line);
        line = get_next_line(fd);
        index++;
    }
    g_map[index] = NULL;
    close(fd);
    return (g_map);
}