#include "../cub3d.h"

void    chech_direction(char **map, int index, int jndex)
{
    if (map[index] == NULL)
        _error("Parssing");
    else if (map[index][jndex] != '\0' && map[index][jndex] != '\n')
    {
        if (map[index][jndex] == SPACE)
            _error("Parssing");
    }
    else
        _error("Parssing");
}