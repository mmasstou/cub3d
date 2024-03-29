/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_textureUtils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 12:42:42 by mmasstou          #+#    #+#             */
/*   Updated: 2022/09/09 18:26:08 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	adding_texture(t_texture **lst, t_texture *new)
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

static t_texture	*get_textures_data(
	void *mlx_ptr, char *texture_name, int type)
{
	t_texture	*tmp;
	void		*mlx_image;
	int			bits_per_pixel;
	int			size_line;
	int			endian;

	tmp = (t_texture *)malloc(sizeof(t_texture));
	tmp->type = type;
	mlx_image = mlx_xpm_file_to_image(\
	mlx_ptr, texture_name, &(tmp->width), &(tmp->height));
	if (mlx_image == NULL)
		return (NULL);
	tmp->buff = (int *)mlx_get_data_addr(\
	mlx_image, &bits_per_pixel, &size_line, &endian);
	if (!tmp->buff)
		return (NULL);
	tmp->next = NULL;
	return (tmp);
}

void	init_textures(t_data *data)
{
	data->tex = NULL;
	adding_texture(&data->tex, \
	get_textures_data(data->mlx_vars->mlx_ptr, data->ea, TEX_EA));
	adding_texture(&data->tex, \
	get_textures_data(data->mlx_vars->mlx_ptr, data->so, TEX_SO));
	adding_texture(&data->tex, \
	get_textures_data(data->mlx_vars->mlx_ptr, data->we, TEX_WE));
	adding_texture(&data->tex, \
	get_textures_data(data->mlx_vars->mlx_ptr, data->no, TEX_NO));
}

static t_texture	*find_texture(t_texture *tex, int type)
{
	while (tex)
	{
		if (tex->type == type)
			return (tex);
		tex = tex->next;
	}
	return (NULL);
}

t_texture	*get_texture(t_texture *tex, t_rays *ray)
{
	int	type;

	type = 0;
	if (ray->was_hit_vertical)
	{
		if (ray->angle <= 3 * M_PI_2 && ray->angle >= M_PI_2)
			type = TEX_WE;
		else
			type = TEX_EA;
	}
	else if (ray->was_hit_horizontal)
	{
		if (ray->angle >= 0 && ray->angle <= M_PI)
			type = TEX_SO;
		else
			type = TEX_NO;
	}
	return (find_texture(tex, type));
}
