#include "cub3d.h"

/**
* TODO
* check Args  -> if  argc == 2
* if .cub is exist
* check if map opened 
* The map must be closed/surrounded by walls, if not the program must return
an error
*/

void    checkargs(int argc, char *argv[], t_data *data)
{
    char    *map_name;
    int     j = 0;
    int     t = 0;

    if (argc  != 2)
        cub_error("args", "argument required", NULL);
    map_name = ft_strrchr(argv[1], '.');
    if ((map_name && ft_strcmp(map_name, ".cub") != 0) || !map_name)
        cub_error(argv[1], "a map in format *.cub", NULL);
    stock_data(argv[1], &data);
    while (data->m[j])
    {
        t = -1;
        while (data->m[j][++t])
            printf("%d,%d]-%d-", j, t, data->m[j][t]);
        j++;
        printf("\n");
    }
}