#include "../cub3d.h"

void    parsing_minimap(char **g_map, t_data *data)
{
    int index;
    
    index = 0;
    while (g_map[index])
    {
        if (ft_strncmp("NO", g_map[index],2) != 0 &&
            ft_strncmp("SO", g_map[index], 2) != 0 &&
            ft_strncmp("WE", g_map[index], 2) != 0 &&
            ft_strncmp("EA", g_map[index], 2) != 0 &&
            ft_strncmp("F", g_map[index], 1) != 0 &&
            ft_strncmp("C", g_map[index], 1) != 0 &&
            g_map[index][0] != '\n')
            {
                check_minimap(&g_map[index], data);
                return ;
            }
        index++;
    }
}