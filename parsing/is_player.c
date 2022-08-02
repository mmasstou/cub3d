#include "../cub3d.h"

bool    is_player(char c)
{
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