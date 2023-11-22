/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellakr <abellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 18:11:18 by mmasstou          #+#    #+#             */
/*   Updated: 2022/09/11 16:25:41 by abellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//-------------------------------------------------- graphic
void	graphic(t_data *data)
{
	t_mlx	*mlx;

	data->mlx_vars = (t_mlx *)malloc(sizeof(t_mlx));
	if (!data->mlx_vars)
		_error(NULL);
	mlx = data->mlx_vars;
	mlx->mlx_ptr = mlx_init();
	if (mlx->mlx_ptr == NULL)
		_error("MLX error");
	mlx->mlx_window = mlx_new_window(mlx->mlx_ptr, W, H, "cub3d");
	mlx->mlx_image = mlx_new_image(mlx->mlx_ptr, W, H);
	mlx->buffer = mlx_get_data_addr(\
	mlx->mlx_image, &mlx->bpp, &mlx->line_lenght, &mlx->endian);
	init_textures(data);
	draw_all(data);
	mlx_put_image_to_window(\
	mlx->mlx_ptr, mlx->mlx_window, mlx->mlx_image, 0, 0);
	mlx_hook(mlx->mlx_window, KEYPRESS, 1L << 0, kay_press, data);
	mlx_hook(mlx->mlx_window, KEYRELEASE, 1L << 1, kay_releass, data);
	mlx_hook (mlx->mlx_window, 17, 1L << 0, close_cross, data);
	mlx_hook (data->mlx_vars->mlx_window, 4, 1L << 0, mouse_press, data);
	mlx_hook (data->mlx_vars->mlx_window, 5, 1L << 0, mouse_release, data);
	mlx_hook (data->mlx_vars->mlx_window, 6, 1L << 0, mouse_move, data);
	mlx_loop_hook(mlx->mlx_ptr, looop__hooking, data);
	mlx_loop (mlx->mlx_ptr);
}

//------------------------------------- bonus
void	draw_all(t_data *data)
{
	draw_ceilling_floor(data);
	ray_caste(data);
	draw_circle(RADIUS, data);
	draw__map(data);
	draw__fov(data);
}

//------------------------------------------------ redraw 
void	re_draw__(t_data *data)
{
	t_mlx	*mlx;

	mlx = data->mlx_vars;
	mlx_clear_window(mlx->mlx_ptr, mlx->mlx_window);
	mlx_destroy_image(mlx->mlx_ptr, mlx->mlx_image);
	mlx->mlx_image = mlx_new_image(mlx->mlx_ptr, W, H);
	mlx->buffer = mlx_get_data_addr(\
	mlx->mlx_image, &mlx->bpp, &mlx->line_lenght, &mlx->endian);
	draw_all(data);
	mlx_put_image_to_window(\
	mlx->mlx_ptr, mlx->mlx_window, mlx->mlx_image, 0, 0);
}

//---------------------------------------------------- draw fieald of view 
void	draw__fov(t_data *data)
{
	t_rays	*tmp;
	t_pos	p1;
	t_pos	p2;

	tmp = data->rays;
	data->color_circle = 0;
	translation_player(data);
	while (tmp)
	{
		translation_fov(data, tmp->wall_hit.x, tmp->wall_hit.y);
		data->player->color = BLACK;
		p1.i = (int)data->x_translation;
		p1.j = (int)data->y_translation;
		p2.i = (int)data->x_fov;
		p2.j = (int)data->y_fov;
		draw_line(data, p1, p2);
		tmp = tmp->next;
	}
}

//------------------------------------------------------------------------
int	draw__map(t_data *data)
{
	int	index;
	int	jndex;

	index = 0;
	data->unit = 30;
	while (data->map[index])
	{
		jndex = 0;
		while (data->map[index][jndex] && data->map[index][jndex] != '\n')
		{
			data->unit_x = jndex * data->unit;
			data->unit_y = index * data->unit;
			translation_map(data);
			if (data->map[index][jndex] == '0' || \
			ft_strchr("SNWE", data->map[index][jndex]) != NULL)
				draw_rect(data->x_translation, data->y_translation, \
				data, EMPTY_SPACE);
			else if (data->map[index][jndex] == '1')
				draw_rect(data->x_translation, data->y_translation, data, WALL);
			jndex ++;
		}
		index ++;
	}
	return (0);
}
