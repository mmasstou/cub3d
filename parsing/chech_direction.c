#include "../cub3d.h"

void    chech_direction(char **map, int index, int jndex)
{
    if (map[index] == NULL)
        _error("space with zero down");
    else if (map[index][jndex] != '\0' && map[index][jndex] != '\n')
    {
        if (map[index][jndex] == SPACE)
            _error("space with zero down");
    }
    else
        _error("space with zero down");
}