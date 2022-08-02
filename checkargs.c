#include "cub3d.h"

void     checkargs(int argc, char *argv[])
{
    char    *map_name;

    if (argc  != 2)
        _error("argument required");
    map_name = ft_strrchr(argv[1], '.');
    if ((map_name && ft_strcmp(map_name, ".cub") != 0) || !map_name)
    {   
        _error("a map in format *.cub");
    }
    if (open(argv[1], O_RDONLY, 0777) == -1)
         _error("Can`t Open Map");
}