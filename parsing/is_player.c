/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_player.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 11:24:23 by mmasstou          #+#    #+#             */
/*   Updated: 2022/08/05 11:58:21 by mmasstou         ###   ########.fr       */
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
		return (true);
	else if (c == 'N')
		return (true);
	else if (c == 'S')
		return (true);
	else if (c == 'E')
		return (true);
	return (false);
}
