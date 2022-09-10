/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ceilling_floor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellakr <abellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 09:03:56 by mmasstou          #+#    #+#             */
/*   Updated: 2022/09/10 12:01:04 by abellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//--------------------------------------------------------
void    draw_ceilling_floor(t_data *data)
{
    int index;
    int jndex;
    int color;
	double percent;

    index = H;
	int i = 0;
    while (--index >= H / 2)
    {
		color = ft_rgb(0, data->f.r,data->f.g, data->f.b);
		percent = percent_function(i , H / 2);
		color = shadowing_function(color, percent);
		i+=3;
		jndex = 0;
        while (jndex < W)
        	my_mlx_pixel_put(jndex++, index, data, color);
    }
	index = -1;
	i = 0;
	while(++index <= H / 2)
	{
		color = ft_rgb(0, data->c.r,data->c.g, data->c.b);	
		percent = percent_function(i, H / 2);
		color = shadowing_function(color, percent);
		i+=3;
		jndex = 0;
		while (jndex < W)
        	my_mlx_pixel_put(jndex++, index, data, color);
	}
}
//-------------------------------------------------
double	percent_function(double value, double max_value)
{
	double percent = 100 / (max_value / value);
	return(percent);
}
//----------------------------------------------
int shadowing_function(int color, double percent)
{
	int red;
	int green;
	int blue;

	red = color >> 16;
	red &= 255;
	green = color >> 8;
	green &= 255;
	blue = color >> 0;
	blue &= 255;
	red /= (100 + percent) / 100;
	green /= (100 + percent) / 100;
	blue /= (100 + percent) / 100;
	return(red << 16 | green << 8 | blue << 0);
}