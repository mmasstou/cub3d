/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 18:39:23 by mmasstou          #+#    #+#             */
/*   Updated: 2022/07/31 23:26:18 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	*ft_reassign(void *oldptr, void *newptr)
{
	free(oldptr);
	return (newptr);
}

void    parsing_map(char **g_map, t_data *data, int g_map_size)
{
    int index;
    int jndex;
    
    (void)data;
    index = 0;
    // printf("g_map_size : %d\n", g_map_size);
    while (g_map[index])
    {
        // g_map[index] = ft_reassign(g_map[index], ft_strtrim(g_map[index], " "));
        if (ft_strncmp("NO", g_map[index],2) != 0 &&
            ft_strncmp("SO", g_map[index], 2) != 0 &&
            ft_strncmp("WE", g_map[index], 2) != 0 &&
            ft_strncmp("EA", g_map[index], 2) != 0 &&
            ft_strncmp("F", g_map[index], 1) != 0 &&
            ft_strncmp("C", g_map[index], 1) != 0 &&
            g_map[index][0] != '\n')
        {
            printf("line[%2d] : |%s", index, g_map[index]);
            // check map errors
            jndex = 0;
            while (g_map[index][jndex] != '\0' && g_map[index][jndex] != '\n')
            {
                // printf("|%c| -- |%c|\n", g_map[index][jndex], g_map[index][jndex + 1]);
                if (
                    g_map[index][jndex] == 32 &&
                    (((g_map[index][jndex + 1] && g_map[index][jndex + 1] == '0') || (g_map[index][jndex - 1] && g_map[index][jndex - 1] == '0')) ||
                    ((g_map[index - 1][jndex + 1] && g_map[index - 1][jndex + 1] == '0') || (g_map[index - 1][jndex - 1] && g_map[index - 1][jndex - 1] == '0'))
                    )
                    )
                {
                    printf("Map Error\n1->|%c|->|%c|\n", g_map[index][jndex], g_map[index][jndex + 1]);
                    printf("jndex |%d", jndex);
                    exit (1);
                }
                jndex++;
            }
            // return ;
        }
        index++;
    }
}

int get_map_size(char *file)
{
    int index;
    int fd;
    char    *line;

    index = 0;
    printf("file  >>%s\n", file);
    fd = open(file, O_RDONLY, 0777);
    if (fd == -1)
        exit (1);
    line = get_next_line(fd);
    while (line)
    {
        index++;
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    printf("index >>%d\n", index);
    return (index);
}

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

void    parsing(char *argv[], t_data *data)
{
    char    **g_map;
    int     g_map_size;
    int     index;

    g_map = get_g_map(argv[1], &g_map_size);
    parsing_map(g_map, data, g_map_size);
    index = 0;
    while (g_map[index])
    {
        free(g_map[index]);
        index++;
    }
    free(g_map);
    
}