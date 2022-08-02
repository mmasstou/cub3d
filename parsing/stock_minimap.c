#include "../cub3d.h"

void    stock_minimap(char **minimap, t_data **data, int minimap_size)
{
    int index;
    (*data)->map = (char **)malloc(sizeof(char *) * minimap_size + 1);
    if (!(*data)->map)
        _error("malloc");
    index = 0;
    while (minimap[index])
    {
        (*data)->map[index] = ft_strdup(minimap[index]);
        index++;
    }
    (*data)->map[index] = NULL;
}