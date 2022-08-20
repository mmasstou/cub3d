
#include "../cub3d.h"

void    draw_ceilling_floor(t_data *data)
{
    int index;
    int jndex;
    int color;

    index = 0;
    color = ft_rgb(0, data->c.r,data->c.g, data->c.b);
    while (index <= H)
    {
        if (index == H / 2)
            color = ft_rgb(12, data->f.r,data->f.g, data->f.b);
        jndex = 0;
        while (jndex <= W)
        {
            my_mlx_pixel_put(jndex, index, data, color);
            jndex++;
        }
        index++;
    }

}