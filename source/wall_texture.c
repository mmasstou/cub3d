/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 12:42:42 by mmasstou          #+#    #+#             */
/*   Updated: 2022/09/02 18:26:51 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	adding_texture(t_texture **lst, t_texture *new)
{
	t_texture	*n;

	if (*lst == NULL)
		*lst = new;
	else
	{
		n = *lst;
		while (n->next != NULL)
			n = n->next;
		n->next = new;
	}
}

void init_textures(t_data *data)
{
	t_texture *tmp;
	
	data->tex = NULL;
	tmp = (t_texture *)malloc(sizeof(t_texture));
	tmp->bits_per_pixel = 0;
	tmp->size_line = 0;
	tmp->endian = 0;
	tmp->width = 0;
	tmp->height = 0;
	tmp->mlx_image = mlx_xpm_file_to_image(data->mlx_vars->mlx_ptr, data->ea, &(tmp->width), &(tmp->height));
	if (tmp->mlx_image == NULL)
		return;
	tmp->buff = mlx_get_data_addr(tmp->mlx_image, &(tmp->bits_per_pixel),  &(tmp->size_line),  &(tmp->endian));
	// data->tex->buff = NULL;
	// printf("buff |%s\n", (char *)mlx_image);
	adding_texture(&data->tex, tmp);
	// mlx_put_image_to_window(data->mlx_vars->mlx_ptr, data->mlx_vars->mlx_window, mlx_image, tmp->width, tmp->height);
	printf("%s %d, %d\n", tmp->buff, tmp->width, tmp->height);
	// printf("buff |%s\n", data->tex->buff);
}