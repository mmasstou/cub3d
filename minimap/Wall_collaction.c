/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wall_collaction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 16:54:59 by mmasstou          #+#    #+#             */
/*   Updated: 2022/08/22 20:33:15 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	wall_collaction(float index, float jndex, t_data *data){
	int i=0, j;
	int x, y;

	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			printf("%c", data->map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	x = (int)index;
	y = (int)jndex;
	printf(" -%d-%d- @ x = %d, y = %d\n",i, j, x, y);
	// printf("data->map[%d]=|%s", 26, data->map[26]);
	// printf("data->map[%d]=|%s", y, data->map[x]);
	// printf("--*> data->map[%d][%d]=|%c|\n", y, x, data->map[y][x]);
	if (data->map[y] != NULL && (data->map[y][x] == '0'))
		return (1);
	return (0);
	
}