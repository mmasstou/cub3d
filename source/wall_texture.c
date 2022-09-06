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

t_texture	*get_textures_data(void *mlx_ptr, char *texture_name, int type)
{
	t_texture *tmp;
	void	*mlx_image;
	int 	bits_per_pixel;
	int 	size_line;
	int 	endian;
	
	tmp = (t_texture *)malloc(sizeof(t_texture));
	tmp->type = type;
	mlx_image = mlx_xpm_file_to_image(mlx_ptr, texture_name, &(tmp->width), &(tmp->height));
	if (mlx_image == NULL)
		return (NULL);
	tmp->buff = (int *)mlx_get_data_addr(mlx_image, &bits_per_pixel,  &size_line,  &endian);
	if (!tmp->buff)
		return (NULL);
	tmp->next = NULL;
	return (tmp);
}

void init_textures(t_data *data)
{
	data->tex = NULL;
	printf("%s\n", data->ea);
	printf("%s\n", data->so);
	printf("%s\n", data->we);
	printf("%s\n", data->no);
	adding_texture(&data->tex, get_textures_data(data->mlx_vars->mlx_ptr, data->ea, TEX_EA));
	adding_texture(&data->tex, get_textures_data(data->mlx_vars->mlx_ptr, data->so, TEX_SO));
	adding_texture(&data->tex, get_textures_data(data->mlx_vars->mlx_ptr, data->we, TEX_WE));
	adding_texture(&data->tex, get_textures_data(data->mlx_vars->mlx_ptr, data->no, TEX_NO));
}

t_texture *get_texture(t_texture *tex, int type)
{
	while (tex)
	{
		if (tex->type == type)
			return (tex);
		tex = tex->next;
	}
	return (NULL);
}

int get_texture_color(t_rays *ray, t_data *data, int y, int wall_strip_height)
{
	t_position tex_offset;
	double x;
	int color;
	t_texture *tmp;

	(void)wall_strip_height;
	tmp = NULL;

	if (ray->wasHitVertical)
	{
		if (ray->angle <= 3 * M_PI_2 && ray->angle >= M_PI_2)
			tmp = get_texture(data->tex, TEX_WE);
		else 
			tmp = get_texture(data->tex, TEX_EA);
	}
	else if (ray->wasHithorizontal)
	{
		if (ray->angle >= 0 && ray->angle <= M_PI)
			tmp = get_texture(data->tex, TEX_SO);
		else
			tmp = get_texture(data->tex, TEX_NO);
	}
	if (!tmp)
		return (0);
	if (ray->wasHitVertical)
		tex_offset.x = ray->wall_hit.y / data->unit;
	else
		tex_offset.x = ray->wall_hit.x / data->unit;
	tex_offset.x = tex_offset.x - floor(tex_offset.x);
	tex_offset.x *= tmp->width;
	x = y + (ray->wall_strip_height / 2) - (H / 2);
	if (x < 0)
		x = 0;
	tex_offset.y = x * ((double)tmp->height / ray->wall_strip_height) ;
	tex_offset.y = floor(tex_offset.y);
	tex_offset.y *= tmp->width;
	color = tmp->buff[((int)tex_offset.y + (int)tex_offset.x)];
	return(color);
}