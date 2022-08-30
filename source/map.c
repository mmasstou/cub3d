#include "../includes/cub3d.h"

//--------------------------------------------------------------------------------
void	my_mlx_pixel_put(int x, int y, t_data *data, int color)
{
	char	*dst;

	if ((x >= 0 && x < W) && (y >= 0 && y < H))
	{
		dst = data->mlx_vars->buffer + (y * data->mlx_vars->line_lenght + x * (data->mlx_vars->bpp / 8));
		*(unsigned int *)dst = color;
	}
}
//--------------------------------------------------------------------------------
void    draw_rect(float x, float y, t_data *data, int color, int type)
{
	int index;
	int jndex;
	int old__y;
	
	index = (x + data->unit);
	jndex = (y + data->unit); 
	old__y = y;
	while (x <= index - type)
	{
		y = old__y;
		while (y <= jndex - type)
		{
            if(sqrt(pow(x - data->centre, 2) + pow(y - data->centre, 2)) < RADIUS)	
				my_mlx_pixel_put(x, y, data, color);
			y++;
		}
		x++;
	}
}
//---------------------------------------------------------------------------
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
//------------------------------------------------------------------------
int	draw__map(t_data *data){
	
	int index = 0;
	int jndex = 0;
	int rect_color;
	int i = 0;
	data->unit = 30;
	while (data->map[index])
	{
		jndex = 0;
		while (data->map[index][jndex])
		{
			i = 0;
			data->unit_x = jndex * data->unit;
			data->unit_y = index * data->unit;
			translation_map(data);
			if (data->map[index][jndex] == '1')
			{
				i = 2;
				rect_color = WALL;
			}
			else if (data->map[index][jndex] == '0' || ft_strchr("SNWE", data->map[index][jndex]) != NULL)
				rect_color = EMPTY_SPACE;
			else if (data->map[index][jndex++] == ' ')
				continue;
			draw_rect(data->x_translation, data->y_translation, data, rect_color, i);
			jndex ++;
		}
		index ++;
	}
	return (0);
}
//----------------------------------------------------------------
int	arraylen(char **array){
	int index;

	index = -1;
	while (array[++index])
		;
	return (index);
}
//-----------------------------------------------------------------------
int	wall_collaction(float index, float jndex, t_data *data)
{
	
	int x;
	int y;
	int	array_len = arraylen(data->map);
	int k;

	x = floor(index);
	y = floor(jndex);
	if(y > array_len)
		return (1);
	if (y >= 0 && data->map[y] != NULL)
	{
		k = ft_strlen(data->map[y]);
		if (x > k && x >= 0)
			return (1);
		if (x <= k && (data->map[y][x] == '1' || data->map[y][x] == ' '))
			return (1);
		else if (data->map[y][x] == '0')
			return (0);
	}
	return (2);
	
}
//----------------- draw line function  for circle
void    dda_circle(double x1, double y1,double x2, double y2,t_data *vars)
{
    float    steps;
    float    dx;
    float    dy;

    dx = x2 - x1;
    dy = y2 - y1;
    if (fabsf(dx) > fabsf(dy))
        steps = fabsf(dx);
    else
        steps = fabsf(dy);
    dx /= steps;
    dy /= steps;
    while ((int)(x1 - x2) || (int)(y1 - y2))
    {
        my_mlx_pixel_put(x1 , y1 , vars, vars->color_circle);
        x1 += dx;
        y1 += dy;
    }
}
//------------------------------------------- translation map
void	translation_map(t_data *data)
{
	data->k_x = data->ply->x_pos * data->unit - data->centre;
	data->k_y = data->ply->y_pos * data->unit - data->centre;
	//-----------------------------------------
	if(data->k_x == 0)
		data->x_translation = data->unit_x;
	else if(data->k_x > 0)
		data->x_translation = data->unit_x - fabs(data->k_x);
	else if(data->k_x < 0)
		data->x_translation = data->unit_x + fabs(data->k_x);
		//----------------------------
	if(data->k_y == 0)
		data->y_translation = data->unit_y;
	else if(data->k_y < 0)
		data->y_translation = data->unit_y + fabs(data->k_y);
	else if(data->k_y > 0)
		data->y_translation = data->unit_y - fabs(data->k_y);
}
//------------------------------------------ draw circle function
void DrawCircle(int r, t_data *data)
{
    double i;
	double angle;
	double x1;
	double  y1;
	
	i = 0;
	data->color_circle = WHITE;
	data->centre = r + BORDER;
	while(i < 360)
	{
        angle = i;
        x1 = r * cos(angle * M_PI / 180) + r;
        y1 = r * sin(angle * M_PI / 180) + r;
        dda_circle(r + BORDER, r + BORDER, x1 + BORDER, y1 + BORDER, data);
		i+=0.01;
    }
}
