/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw__fov.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 09:21:57 by mmasstou          #+#    #+#             */
/*   Updated: 2022/09/02 12:33:12 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../includes/cub3d.h"

// void	draw__fov(t_data *data)
// {
// 	t_rays *tmp;
// 	tmp = data->rays;
// 	while (tmp)
// 	{
// 		data->player->color = ft_rgb(40, FOV_COLOR);
// 		draw_line(
// 			data,
// 			data->player->pos.x * data->unit * FACTO,
// 			data->player->pos.y * data->unit * FACTO,
// 			tmp->wall_hit.x * FACTO,
// 			tmp->wall_hit.y * FACTO
// 		);
// 		tmp = tmp->next;
// 	}
// }