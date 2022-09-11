/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellakr <abellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 09:05:40 by mmasstou          #+#    #+#             */
/*   Updated: 2022/09/11 16:19:17 by abellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	loop(t_line *var, t_pos *p1, t_pos *p2, t_data *data)
{
	while (1)
	{
		if (sqrt(pow(p1->i - data->centre, 2) + pow(p1->j - data->centre, 2)) \
		<= RADIUS)
			my_mlx_pixel_put(p1->i, p1->j, data, data->player->color);
		var->e2 = 2 * var->e1;
		if (var->e2 >= var->dy)
		{
			if (p1->i == p2->i)
				break ;
			var->e1 += var->dy;
			p1->i += var->sx;
		}
		if (var->e2 <= var->dx)
		{
			if (p1->j == p2->j)
				break ;
			var->e1 += var->dx;
			p1->j += var->sy;
		}
	}
}

// -----------------------------------------------------------------------------
void	draw_line(t_data *data, t_pos p1, t_pos p2)
{
	t_line	var;

	var.dx = abs(p2.i - p1.i);
	var.dy = -abs(p2.j - p1.j);
	if (p1.i < p2.i)
		var.sx = 1;
	else
		var.sx = -1;
	if (p1.j < p2.j)
		var.sy = 1;
	else
		var.sy = -1;
	var.e1 = var.dx + var.dy;
	loop(&var, &p1, &p2, data);
}
