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
	void	*mlx_image;
	
	data->tex = NULL;
	tmp = (t_texture *)malloc(sizeof(t_texture));
	tmp->type = TEX_EA;
	mlx_image = mlx_xpm_file_to_image(data->mlx_vars->mlx_ptr, data->ea, &(tmp->width), &(tmp->height));
	if (mlx_image == NULL)
		return;
	tmp->buff = (int *)mlx_get_data_addr(mlx_image, &(tmp->bits_per_pixel),  &(tmp->size_line),  &(tmp->endian));
	if (!tmp->buff)
		return;
	tmp->next = NULL;
	adding_texture(&data->tex, tmp);
}

int get_texture_color(t_rays *ray, t_data *data, int y, int wall_strip_height)
{
	t_position tex_offset;
	double x;

	if (ray->wasHitVertical)
		tex_offset.x = ray->wall_hit.y / data->unit;
	else
		tex_offset.x = ray->wall_hit.x / data->unit;
	tex_offset.x = tex_offset.x - floor(tex_offset.x);
	tex_offset.x *= data->tex->width;
	x = (H / 2) - (wall_strip_height / 2);
	if (x < 0)
		x = 0;
	tex_offset.y = (y - x) * ((double)data->tex->height / ray->wall_strip_height) ;
	tex_offset.y = floor(tex_offset.y);
	// tex_offset.y += (ray->wall_strip_height - wall_strip_height) / 2;
	tex_offset.y *= data->tex->width;
	// printf("tex_offset.x :%f, tex_offset.y :%f **> %d\n",tex_offset.x, tex_offset.y, data->tex->buff[(int)(tex_offset.y + tex_offset.x)]);
	return(data->tex->buff[((int)tex_offset.y + (int)tex_offset.x)]);
}