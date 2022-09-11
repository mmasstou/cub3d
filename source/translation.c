/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellakr <abellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 11:58:08 by abellakr          #+#    #+#             */
/*   Updated: 2022/09/11 11:58:40 by abellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//------------------------------------------- translation fov
void translation_fov(t_data *data, float x, float y)
{
	data->k_x = data->player->pos.x * data->unit - data->centre;
	data->k_y = data->player->pos.y * data->unit - data->centre;
	if(data->k_x == 0)
		data->x_fov = x;
	else if(data->k_x > 0)
		data->x_fov = x - fabs(data->k_x);
	else if(data->k_x < 0)
		data->x_fov = x + fabs(data->k_x);
	if(data->k_y == 0)
		data->y_fov = y;
	else if(data->k_y < 0)
		data->y_fov = y + fabs(data->k_y);
	else if(data->k_y > 0)
		data->y_fov = y - fabs(data->k_y);
}
//-------------------------------------------------------------
void	translation_player(t_data *data)
{
	data->k_x = data->player->pos.x * data->unit - data->centre;
	data->k_y = data->player->pos.y * data->unit - data->centre;
	if(data->k_x == 0)
		data->x_translation = data->player->pos.x * data->unit;
	else if(data->k_x > 0)
		data->x_translation = data->player->pos.x * data->unit - fabs(data->k_x);
	else if(data->k_x < 0)
		data->x_translation = data->player->pos.x * data->unit + fabs(data->k_x);
	if(data->k_y == 0)
		data->y_translation = data->player->pos.y * data->unit;
	else if(data->k_y < 0)
		data->y_translation = (data->player->pos.y * data->unit) + fabs(data->k_y);
	else if(data->k_y > 0)
		data->y_translation = (data->player->pos.y * data->unit) - fabs(data->k_y);
}
//------------------------------------------- translation map
void	translation_map(t_data *data)
{
	data->k_x = data->player->pos.x * data->unit - data->centre;
	data->k_y = data->player->pos.y * data->unit - data->centre;
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