#include "../cub3d.h"

bool    is_player(char c, t_data *data)
{
     if (data->p == 0)
        data->p = c;
    else
        _error("multiple player ");
    if (c == 'W')
        return (true);
    else if (c == 'N')
        return (true);
    else if (c == 'S')
        return (true);
    else if (c == 'E')
        return (true);
    return (false);
}