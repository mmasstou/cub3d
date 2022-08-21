/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_player.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 11:24:23 by mmasstou          #+#    #+#             */
/*   Updated: 2022/08/21 16:18:52 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	is_player(char c, t_data *data)
{
	if (data->p == 0)
		data->p = c;
	else
		_error("multiple player ");
	if (c == 'W')
		return (data->ply->spawning_orientation = c,true);
	else if (c == 'N')
		return (data->ply->spawning_orientation = c,true);
	else if (c == 'S')
		return (data->ply->spawning_orientation = c,true);
	else if (c == 'E')
		return (data->ply->spawning_orientation = c,true);
	
	return (false);
}
