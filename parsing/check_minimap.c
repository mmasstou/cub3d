#include "../cub3d.h"

void    check_minimap(char **minimap, t_data *data)
{
    int index;
    int jndex;
    int m;

    index = 0;
    data->p = 0;
    while (minimap[index])
    {
        jndex = 0;
        while (minimap[index][jndex] != '\0' && minimap[index][jndex] != '\n')
        {
            if (minimap[index][jndex] == ZERO)
            {
                chech_direction(minimap, index - 1, jndex);
                chech_direction(minimap, index + 1, jndex);
                chech_direction(minimap, index, jndex - 1);
                chech_direction(minimap, index, jndex + 1);
            }
            else if (minimap[index][jndex] == SPACE)
                m = 1;
            else if (minimap[index][jndex] == ONE)
                m = 1;
            else if (is_player(minimap[index][jndex]) == true)
            {
                if (data->p == 0)
                    data->p = minimap[index][jndex];
                else
                    _error("multiple player ");
                chech_direction(minimap, index - 1, jndex);
                chech_direction(minimap, index + 1, jndex);
                chech_direction(minimap, index, jndex - 1);
                chech_direction(minimap, index, jndex + 1);
            }
            else 
                _error("Stranger Element");
            jndex++;
        }
        index++;
    }
    stock_minimap(minimap, &data, index + 1);
}
