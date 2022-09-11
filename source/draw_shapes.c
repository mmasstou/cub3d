/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellakr <abellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 11:56:25 by abellakr          #+#    #+#             */
/*   Updated: 2022/09/11 12:05:11 by abellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
