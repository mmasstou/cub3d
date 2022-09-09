/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 18:11:18 by mmasstou          #+#    #+#             */
/*   Updated: 2022/09/09 18:11:23 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
	draw_ceilling_floor(data);
	init_textures(data);
	ray_caste(data);
	mlx_put_image_to_window(\
	mlx->mlx_ptr, mlx->mlx_window, mlx->mlx_image, 0, 0);
	mlx_hook(mlx->mlx_window, KEYPRESS, 1L << 0, kay_press, data);
	mlx_hook(mlx->mlx_window, KEYRELEASE, 1L << 1, kay_releass, data);
	mlx_hook (mlx->mlx_window, 17, 1L << 0, close_cross, data);
	mlx_loop_hook(mlx->mlx_ptr, looop__hooking, data);
	mlx_loop (mlx->mlx_ptr);
}

void	re_draw__(t_data *data)
{
	t_mlx	*mlx;

	mlx = data->mlx_vars;
	mlx_clear_window(mlx->mlx_ptr, mlx->mlx_window);
	mlx_destroy_image(mlx->mlx_ptr, mlx->mlx_image);
	mlx->mlx_image = mlx_new_image(mlx->mlx_ptr, W, H);
	mlx->buffer = mlx_get_data_addr(\
	mlx->mlx_image, &mlx->bpp, &mlx->line_lenght, &mlx->endian);
	draw_ceilling_floor(data);
	ray_caste(data);
	mlx_put_image_to_window(\
	mlx->mlx_ptr, mlx->mlx_window, mlx->mlx_image, 0, 0);
}
