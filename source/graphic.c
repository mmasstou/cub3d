/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellakr <abellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 18:11:18 by mmasstou          #+#    #+#             */
/*   Updated: 2022/09/11 11:59:03 by abellakr         ###   ########.fr       */
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

//------------------------------------- bonus
void	draw_all(t_data *data)
{
	draw_ceilling_floor(data);
	ray_caste(data);
	DrawCircle(RADIUS, data);
	draw__map(data);
	draw__fov(data);
}
//---------------------------------------------------- draw fieald of view 
void	draw__fov(t_data *data)
{
	t_rays *tmp;
	
	tmp = data->rays;
	data->color_circle = 0;
	translation_player(data);
	while(tmp)
	{
		data->x1 = data->x_translation;
		data->y1 = data->y_translation;
		translation_fov(data, tmp->wall_hit.x, tmp->wall_hit.y);
		data->x2 = data->x_fov;
		data->y2 = data->y_fov;
		//color
		data->player->color = BLACK;
		draw_line(data, data->x_translation, data->y_translation, data->x_fov, data->y_fov);
		tmp = tmp->next;
	}
}

//------------------------------------------------------------------------
int	draw__map(t_data *data)
{
	
	int index = 0;
	int jndex;
	data->unit = 30;
	while (data->map[index])
	{
		jndex = 0;
		while (data->map[index][jndex] && data->map[index][jndex] != '\n')
		{
			data->unit_x = jndex * data->unit;
			data->unit_y = index * data->unit;
			translation_map(data);
			if (data->map[index][jndex] == '0' || ft_strchr("SNWE", data->map[index][jndex]) != NULL)
				draw_rect(data->x_translation, data->y_translation, data, EMPTY_SPACE, 0);
			else if (data->map[index][jndex] == '1')
				draw_rect(data->x_translation, data->y_translation, data, WALL, 0);
			jndex ++;
		}
		index ++;
	}
	return (0);
}