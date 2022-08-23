/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wall_collaction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 16:54:59 by mmasstou          #+#    #+#             */
/*   Updated: 2022/08/23 18:51:47 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	wall_collaction(float index, float jndex, t_data *data){
	int x;
	int y;
	x = (int)index;
	y = (int)jndex;
	printf("*wall_collaction*+>%f - $%f\n", index, jndex);
	if (data->map[y] != NULL){
		if (data->map[y][x] == '0'){
			// printf(">>>>> NO Wall\n");
			return (0);	
		}
		if (data->map[y][x] == '1' || data->map[y][x] == ' '){
			// printf(">>>>> Wall\n");
			return (1);	
		}
	}
	return (0);
	
}