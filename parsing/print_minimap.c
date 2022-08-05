/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 12:00:33 by mmasstou          #+#    #+#             */
/*   Updated: 2022/08/05 12:13:45 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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