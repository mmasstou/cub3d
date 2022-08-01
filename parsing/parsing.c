/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 18:39:23 by mmasstou          #+#    #+#             */
/*   Updated: 2022/08/01 22:07:43 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	*ft_reassign(void *oldptr, void *newptr)
{
	free(oldptr);
	return (newptr);
}

void    _error(char *msg)
{
    ft_putstr_fd("\033[0;31m", STDERR_FILENO);
    ft_putstr_fd("❌ Error :", STDERR_FILENO);
    if (msg != NULL)
        ft_putstr_fd(msg, STDERR_FILENO);
    ft_putendl_fd("\033[0m", STDERR_FILENO);
    exit(1);
}
# define ZERO '0'
# define ONE '1'
# define SPACE ' '

void map_freme(char **g_map, int g_map_size, int i)
{
    int j;

    j = 0;
    printf("first LIine |%s\n", g_map[i]);
    printf("last LIine  |%s\n", g_map[g_map_size - 1]);
    while (g_map[i][j] && g_map[i][j] != '\n')
    {
        if (g_map[i][j] != '1')
            if (g_map[i][j] != ' ')
                _error("map not closed 1 !");
        j++;
    }
    j = 0;
    while (g_map[g_map_size - 1][j] && g_map[g_map_size - 1][j] != '\n')
    {
        if (g_map[g_map_size - 1][j] != '1')
            if (g_map[g_map_size - 1][j] != ' ')
                _error("map not closed 2 !");
        j++;
    }
    while (g_map[++i])
    {
        j = 0;
        while (g_map[i][j] && g_map[i][j] != '\n' && g_map[i][j] == ' ')
            j++;
        if (g_map[i][j] != '1')
            _error("map not closed 3 !");
        else if (g_map[i][ft_strlen(g_map[i]) - 2] != '1')
        {
            printf(">>>>%c<<%s<\n", g_map[i][ft_strlen(g_map[i]) - 2], g_map[i]);
            _error("map not closed 4 !");
        }
    }
}
void    chech_direction(char **map, int index, int jndex, int dirc)
{
    int m;
    if (map[index] == NULL)
        _error("space with zero down");
    else if (map[index][jndex] != '\0' || map[index][jndex] != '\n')
    {
        if (map[index][jndex] == SPACE)
            _error("space with zero down");
    }
}

// void    check_minimap(char **minimap, t_data *data)
// {
//     int index;
//     int jndex;

//     index = 0;
//     jndex = 0;
//     while (minimap[index])
//     {
//         while (minimap[index][jndex] != '\0' && minimap[index][jndex] != '\n')
//         {
//             if (minimap[index][jndex] == ZERO)
//             {
//                 // check 0 up -&-
//                 chech_direction(minimap, index - 1, jndex, NORD);
//                 // check 0 down -&-
//                 chech_direction(minimap, index + 1, jndex, SOUTH);
//                 // check 0 left -&-
//                 chech_direction(minimap, index, jndex - 1, WEST);
//                 // check 0 right -&-
//                 chech_direction(minimap, index, jndex + 1, EAST);
//                 printf("%s", "🍀");
//             }
//             else if (minimap[index][jndex] == SPACE)
//                 printf("%s", "  ");
//             jndex++;
//         }
//        index++;
//     }
    
// }
void    parsing_map(char **g_map, t_data *data, int g_map_size)
{
    int index;
    int jndex;
    int i;
    int m;
    
    (void)data;
    // printf("g_map_size : %d\n", g_map_size);
    index = 0;
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
            // check map errors
            // map_freme(g_map, g_map_size, i);
            while (true)
            {
                // printf("line[%2d] : |%s", index, g_map[index]);
                jndex = 0;
                while (g_map[index] && g_map[index][jndex] != '\0' && g_map[index][jndex] != '\n')
                {
                    // -&- check 0 -&-
                    if (g_map[index][jndex] == ZERO)
                    {
                        // check 0 up -&-
                        chech_direction(g_map, index - 1, jndex, NORD);
                        // check 0 down -&-
                        chech_direction(g_map, index + 1, jndex, SOUTH);
                        // check 0 left -&-
                        chech_direction(g_map, index, jndex - 1, WEST);
                        // check 0 right -&-
                        chech_direction(g_map, index, jndex + 1, EAST);
                        printf("%s", "🍀");
                    }
                    // -&- check 1 -&-
                    else if (g_map[index][jndex] == SPACE)
                        printf("%s", "  ");
                    else if (g_map[index][jndex] != SPACE && g_map[index][jndex] != ZERO && g_map[index][jndex] != ONE)
                    {
                        // check 0 up -&-
                        chech_direction(g_map, index - 1, jndex, NORD);
                        // check 0 down -&-
                        chech_direction(g_map, index + 1, jndex, SOUTH);
                        // check 0 left -&-
                        chech_direction(g_map, index, jndex - 1, WEST);
                        // check 0 right -&-
                        chech_direction(g_map, index, jndex + 1, EAST);
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