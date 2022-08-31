/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellakr <abellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 18:35:37 by mmasstou          #+#    #+#             */
/*   Updated: 2022/08/31 18:43:06 by abellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
void    draw_rect(double x, double y, t_data *data, int color, int type)
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
            color = ft_rgb(0, data->f.r,data->f.g, data->f.b);
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
	int jndex;
	data->unit = 30;
	while (data->map[index])
	{
		jndex = 0;
		while (data->map[index][jndex] && data->map[index][jndex] != '\n')
		{
			data->unit_x = jndex * data->unit;
			data->unit_y = index * data->unit;
			translation_map(data);
			if (data->map[index][jndex] == '0' || ft_strchr("SNWE", data->map[index][jndex]) != NULL)
				draw_rect(data->x_translation, data->y_translation, data, EMPTY_SPACE, 0);
			else if (data->map[index][jndex] == '1')
				draw_rect(data->x_translation, data->y_translation, data, WALL, 0);
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
	int	array_len;
	int str_len;

	array_len = arraylen(data->map);
	x = (int)index;
	y = (int)jndex;

	if(y > array_len || y < 0)
		return (1);
	if (y >= 0 && data->map[y] != NULL)
	{
		str_len = ft_strlen(data->map[y]);
		if (x > str_len || x < 0)
			return (1);
		else if (data->map[y][x] == '1' || data->map[y][x] == ' ')
			return (1);
		else if (data->map[y][x] == '0' || ft_strchr("SWNE", data->map[y][x]) != NULL)
			return (0);
	}
	return (1);
	
}
//----------------- draw line function  for circle
void    dda_circle(double x1, double y1,double x2, double y2,t_data *vars)
{
    double    steps;
    double    dx;
    double    dy;

    dx = x2 - x1;
    dy = y2 - y1;
    if (fabs(dx) > fabs(dy))
        steps = fabs(dx);
    else
        steps = fabs(dy);
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
	if(data->k_x > 0)
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
//-----------------------------------------------------------------------------
void draw_line(t_data *data, int x, int y, int x1, int y1)
{
    int dx, dy, err, sx,sy,e2;

    dx = abs(x1 - x);
    dy = -abs(y1 - y);
    sx = x < x1 ? 1 : -1;
    sy = y < y1 ? 1 : -1;
    err = dx + dy;
    while (1)
    {
        if(sqrt(pow(x - data->centre, 2) + pow(y - data->centre, 2)) < RADIUS)	
        	my_mlx_pixel_put(x,y,data,data->ply->color);
        e2 = 2*err;
        if (e2 >= dy) 
        { /* e_xy+e_x > 0 */
            if (x == x1)
                break;
            err += dy;
            x += sx;
         }
         if (e2 <= dx) 
        { /* e_xy+e_y < 0 */
            if (y == y1) 
                 break;
            err += dx;
            y += sy;
         }
    }
}