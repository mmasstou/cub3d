#include "cub3d.h"

void	my_mlx_pixel_put(int x, int y, t_data *data, int color)
{
	char	*dst;

	if ((x >= 0 && x < W) && (y >= 0 && y < H))
	{
		dst = data->mlx_vars->buffer + (y * data->mlx_vars->line_lenght + x * (data->mlx_vars->bpp / 8));
		*(unsigned int *)dst = color;
	}
}
void    draw_rect(float x, float y, t_data *data, int color, int type)
{
	int index;
	int jndex;
	int i;
	int j;
	
	index = (x + data->unit);
	i = (y + data->unit); 
	j = y;
	while (x <= index - type)
	{
		jndex = i;
		y = j;
		while (y <= jndex - type)
		{
			my_mlx_pixel_put(x, y, data, color);
			y++;
		}
		x++;
	}
}

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

int	draw__map(t_data	*data){
	
	int index = 0;
	int jndex = 0;
	int rect_color;
	int i;
	data->unit = 20;
	while (data->map[index])
	{
		jndex = 0;
		while (data->map[index][jndex])
		{
			i = 2;
			if (data->map[index][jndex] == '1')
			{
				i = 0;
				rect_color = WALL;
			}
			else if (data->map[index][jndex] == '0' || ft_strchr("SNWE", data->map[index][jndex]) != NULL)
				rect_color = EMPTY_SPACE;
			else if (data->map[index][jndex++] == ' ')
				continue;
			draw_rect(jndex * data->unit, index * data->unit, data, rect_color, i);
			jndex ++;
		}
		index ++;
	}
	return (0);
}

int	wall_collaction(float index, float jndex, t_data *data){
	int x;
	int y;

	x = (int)index;
	y = (int)jndex;
	if (data->map[y] != NULL){
		if (data->map[y][x] == '1' || data->map[y][x] == ' '){
			return (1);	
		}
	}
	return (0);
	
}