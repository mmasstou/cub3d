/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellakr <abellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 09:05:40 by mmasstou          #+#    #+#             */
/*   Updated: 2022/09/10 14:58:34 by abellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
        	my_mlx_pixel_put(x,y,data,data->player->color);
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