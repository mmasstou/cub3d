/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_player.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellakr <abellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 11:24:23 by mmasstou          #+#    #+#             */
/*   Updated: 2022/08/28 20:18:02 by abellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	is_player(char c, t_data *data)
{
	if (data->p == 0)
		data->p = c;
	else
		_error("multiple player ");
	if (c == 'W')
		return (true);
	else if (c == 'N')
		return (true);
	else if (c == 'S')
		return (true);
	else if (c == 'E')
		return (true);
	return (false);
}
