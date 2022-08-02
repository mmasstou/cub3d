/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 18:39:23 by mmasstou          #+#    #+#             */
/*   Updated: 2022/08/02 18:02:27 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	*ft_reassign(void *oldptr, void *newptr)
{
	free(oldptr);
	return (newptr);
}

void    free_2d(char **map)
{
    int index;

    index = 0;
    while (map[index])
    {
        free(map[index]);
        index++;
    }
    free(map);
}



void    print_minimap(char **g_map)
{
    int index = 0;
    int jndex;
    while (g_map[index])
    {
        jndex = 0;
        while (g_map[index][jndex] != '\0' && g_map[index][jndex] != '\n')
        {
            if (g_map[index][jndex] == ZERO)
                printf("%s", "🍀");
            else if (g_map[index][jndex] == SPACE)
                printf("%s", "  ");
            else if (g_map[index][jndex] == 'W' || g_map[index][jndex] == 'N' || g_map[index][jndex] == 'S' || g_map[index][jndex] == 'E')
            {
                if (g_map[index][jndex] == 'W')
                    printf("%s", "👈");
                else if (g_map[index][jndex] == 'N')
                    printf("%s", "👆");
                else if (g_map[index][jndex] == 'S')
                    printf("%s", "👇");
                else if (g_map[index][jndex] == 'E')
                    printf("%s", "👉");
                else 
                    _error("Stranger Element");
            }
            // -&- check 0 -&-
            else if (g_map[index][jndex] == ONE)
                printf("\033[0;31m%s\033[0m", "🎱");
            else 
                _error("Stranger Element");
            jndex++;
        }
        if (!g_map[index])
            return ;
        printf("\n");
        index++;
    }
}

void    parsing(char *argv[], t_data *data)
{
    char    **g_map;


    g_map = get_g_map(argv[1]);
    parsing_minimap(g_map, data);
    print_minimap(data->map);
    free_2d(data->map);
    free_2d(g_map);
}