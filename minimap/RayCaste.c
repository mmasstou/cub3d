/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RayCaste.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 21:38:03 by mmasstou          #+#    #+#             */
/*   Updated: 2022/08/22 21:42:30 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int ray_caste(t_data *data){
	int colid;
	int num_rays = 120;
	double ray_angle;

	ray_angle = data->ply->rotation_angle - (FOV / 2);

	colid = 0;
	while (colid < num_rays){
		
		colid ++;
	}
	
}