/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 09:05:40 by mmasstou          #+#    #+#             */
/*   Updated: 2022/09/02 09:05:47 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// void    draw_line(t_data *data, int x, int y, int x1, int y1)
// {
//     float    steps;
//     float    dx;
//     float    dy;

//     dx = x1 - x;
//     dy = y1 - y;
//     if (fabsf(dx) > fabsf(dy))
//         steps = fabsf(dx);
//     else
//         steps = fabsf(dy);
//     dx /= steps;
//     dy /= steps;
//     while ((int)(x - x1) || (int)(y - y1))
//     {
//         my_mlx_pixel_put(x , y , data, data->player->color);
//         x += dx;
//         y += dy;
//     }
// }