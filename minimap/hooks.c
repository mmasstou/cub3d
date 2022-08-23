/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 14:24:41 by mmasstou          #+#    #+#             */
/*   Updated: 2022/08/23 13:57:23 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    graphic(t_data *data)
{
    data->mlx_vars = (t_mlx *)malloc(sizeof(t_mlx));
    if(!data->mlx_vars)
        ft_error();
    data->mlx_vars->mlx_ptr = mlx_init();
	if (data->mlx_vars->mlx_ptr == NULL)
		_error("MLX error");
    data->mlx_vars->mlx_window = mlx_new_window ( data->mlx_vars->mlx_ptr, W, H,"cub3d");
    data->mlx_vars->mlx_image = mlx_new_image(data->mlx_vars->mlx_ptr, W, H);
    data->mlx_vars->buffer = mlx_get_data_addr (data->mlx_vars->mlx_image, &data->mlx_vars->bpp, &data->mlx_vars->line_lenght, &data->mlx_vars->endian);
	drawing_minimap(data);
    mlx_put_image_to_window (data->mlx_vars->mlx_ptr, data->mlx_vars->mlx_window, data->mlx_vars->mlx_image, 0, 0);
	mlx_hook(data->mlx_vars->mlx_window, 2, 1L, move_player_press, data);
	mlx_hook (data->mlx_vars->mlx_window, 17, 1L << 0, close_cross, data);
    mlx_loop (data->mlx_vars->mlx_ptr);
}

void	re_draw(t_data *data)
{
	mlx_clear_window(data->mlx_vars->mlx_ptr, data->mlx_vars->mlx_window);
	mlx_destroy_image(data->mlx_vars->mlx_ptr,data->mlx_vars->mlx_image);
    data->mlx_vars->mlx_image = mlx_new_image(data->mlx_vars->mlx_ptr, W, H);
    data->mlx_vars->buffer = mlx_get_data_addr (data->mlx_vars->mlx_image, &data->mlx_vars->bpp, &data->mlx_vars->line_lenght, &data->mlx_vars->endian);
    drawing_minimap(data);
    mlx_put_image_to_window (data->mlx_vars->mlx_ptr, data->mlx_vars->mlx_window, data->mlx_vars->mlx_image, 0, 0);
}
void	rotate_vector(t_data *data, double angle)
{
	data->ply->rotation_angle += angle * data->ply->rotation_speed;
}
int	move_player_press(int key, t_data *data)
{
	float newPlayerx;
	float newPlayery;

	if (key == 53)
	{
		mlx_destroy_image (data->mlx_vars->mlx_ptr, data->mlx_vars->mlx_image);
		mlx_destroy_window (data->mlx_vars->mlx_ptr, data->mlx_vars->mlx_window);
		exit (0);
	}
	else if (key == S_KEY || key == W_KEY)
	{

		if (key == S_KEY)
			data->ply->walk_direction = -1;
		else if (key == W_KEY)
			data->ply->walk_direction = 1;
		newPlayerx = data->ply->x_pos + (cos(data->ply->rotation_angle) * (data->ply->move_speed * data->ply->walk_direction));
		newPlayery = data->ply->y_pos + (sin(data->ply->rotation_angle) * (data->ply->move_speed * data->ply->walk_direction));
		if (wall_collaction(newPlayerx, newPlayery, data) == 0)
		{
			data->ply->x_pos = newPlayerx;
			data->ply->y_pos = newPlayery;
		}
	}
	else if (key == AROW_LEFT || key == AROW_RIGHT)
	{
		if (key == AROW_LEFT)
			data->ply->turn_direction = -1;
		else if (key == AROW_RIGHT)
			data->ply->turn_direction = 1;
		data->ply->rotation_angle += (data->ply->turn_direction * data->ply->rotation_speed);
		if (data->ply->rotation_angle == (2 * M_PI))
			data->ply->rotation_angle = 0;
	}
	else if (key == A_KEY || key == D_KEY)
	{
		if (key == A_KEY || key == D_KEY)
		{
			printf("A_KEY\n");
 		}
		else if (key == D_KEY)
		{
			printf("D_KEY\n");
		}
	}
	else
		return (0);
	
	// printf("|>> %f, %f\n", data->ply->x_pos, data->ply->y_pos);
	re_draw(data);
	return (0);
}
int	move_player_release(int key, t_data *data)
{
	if (key == S_KEY || key == 125)
	{
		printf("DOWN\n");
		data->ply->walk_direction = data->ply->walk_direction;
	}
	if (key == W_KEY || key == 126)
	{
		printf("UP\n");
		data->ply->walk_direction = data->ply->walk_direction;
	}
	if (key == A_KEY || key == 123)
	{
		printf("LEFT\n");
		data->ply->turn_direction = data->ply->turn_direction;
	}
	if (key == D_KEY || key == 124)
	{
		printf("RIGHT\n");
		data->ply->turn_direction = data->ply->turn_direction;
	}
	re_draw(data);
	return (0);
}
int	close_cross(void *param)
{
	(void)param;
	exit (0);
}