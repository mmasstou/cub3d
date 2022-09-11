/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellakr <abellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 11:56:25 by abellakr          #+#    #+#             */
/*   Updated: 2022/09/11 14:19:29 by abellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//------------------------------------------ draw circle function
void DrawCircle(int r, t_data *data)
{
    double i;
	double angle;
	t_pos p1;
	t_pos p2;
	
	i = 0;
	data->color_circle = WHITE;
	data->centre = r + BORDER;
	p1.x = r + BORDER;
	p1.y = r + BORDER;
	while(i < 360)
	{
        angle = i;
        p2.x = (r * cos(angle * M_PI / 180) + r) + BORDER;
        p2.y = (r * sin(angle * M_PI / 180) + r) + BORDER;
        dda_circle(p1, p2,data);
		i+=0.01;
    }
}
//----------------- draw line function  for circle
void    dda_circle(t_pos p1, t_pos p2, t_data *vars)
{
    double    steps;
    double    dx;
    double    dy;

    dx = p2.x - p1.x;
    dy = p2.y - p1.y;
    if (fabs(dx) > fabs(dy))
        steps = fabs(dx);
    else
        steps = fabs(dy);
    dx /= steps;
    dy /= steps;
    while ((int)(p1.x - p2.x) || (int)(p1.y - p2.y))
    {
        my_mlx_pixel_put(p1.x , p1.y , vars, vars->color_circle);
        p1.x += dx;
        p1.y += dy;
    }
}
//--------------------------------------------------------------------------------
void    draw_rect(double x, double y, t_data *data, int color)
{
	int index;
	int jndex;
	int i;
	int j;

	index = (x + data->unit);
	i = (y + data->unit); 
	j = y;
	while (x <= index)
	{
		jndex = i;
		y = j;
		while (y <= jndex)
		{
            if(sqrt(pow(x - data->centre, 2) + pow(y - data->centre, 2)) <= RADIUS)
				my_mlx_pixel_put(x, y, data, color);
			y++;
		}
		x++;
	}
}
