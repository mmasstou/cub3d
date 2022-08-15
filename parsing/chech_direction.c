/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chech_direction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 11:24:05 by mmasstou          #+#    #+#             */
/*   Updated: 2022/08/14 17:59:39 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	chech_direction(char **map, int index, int jndex)
{
	if (map[index] == NULL)
		_error("Parssing");
	else if (map[index][jndex] != '\0' && map[index][jndex] != '\n')
	{
		if (map[index][jndex] == SPACE)
			_error("Parssing");
	}
	else
		_error("Parssing");
}
