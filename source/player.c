/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellakr <abellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 18:35:42 by mmasstou          #+#    #+#             */
/*   Updated: 2022/09/10 14:49:23 by abellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double	degreeto_radian(float angle)
{
	return (angle * (M_PI / 180));
}

int	ft_rgb(int t, int r, int g, int b)
{
	return ((((t * 255) / 100) << 24) | (r << 16) | (g << 8) | b);
}

void	normalize_angle(double *angle)
{
	*angle = fmod(*angle, (2 * M_PI));
	if (*angle < 0)
		*angle += (2 * M_PI);
}

void	init_player(t_player **p)
{
	(*p)->turn_direction = 0;
	(*p)->walk_direction.x = 0;
	(*p)->walk_direction.y = 0;
	(*p)->fov = degreeto_radian(60);
	if ((*p)->orientation == 'N')
		(*p)->rotation_angle = 3 * M_PI_2;
	else if ((*p)->orientation == 'S')
		(*p)->rotation_angle = M_PI_2;
	else if ((*p)->orientation == 'E')
		(*p)->rotation_angle = 0;
	else if ((*p)->orientation == 'W')
		(*p)->rotation_angle = M_PI;
	(*p)->move_speed = 0.1;
	(*p)->rotation_speed = degreeto_radian(5);
}

void	player_update(t_data **data)
{
	float		step;
	t_pos		new_player;
	t_player	*ply;

	ply = (*data)->player;
	step = ply->walk_direction.x * ply->move_speed;
	new_player.x = ply->pos.x - (sin(ply->rotation_angle) * step);
	new_player.y = ply->pos.y + (cos(ply->rotation_angle) * step);
	if (wall_collaction(new_player.x, new_player.y, *data) == 0)
	{
		ply->pos.x = new_player.x;
		ply->pos.y = new_player.y;
	}
	step = ply->walk_direction.y * ply->move_speed;
	ply->rotation_angle += (ply->turn_direction * ply->rotation_speed);
	normalize_angle(&(ply->rotation_angle));
	new_player.x = ply->pos.x + (cos(ply->rotation_angle) * step);
	new_player.y = ply->pos.y + (sin(ply->rotation_angle) * step);
	if (wall_collaction(new_player.x, new_player.y, *data) == 0)
	{
		ply->pos.x = new_player.x;
		ply->pos.y = new_player.y;
	}
}
