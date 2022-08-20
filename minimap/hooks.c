/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 14:24:41 by mmasstou          #+#    #+#             */
/*   Updated: 2022/08/18 04:54:39 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	re_draw(t_data *data)
{
	mlx_clear_window(data->mlx_vars->mlx_ptr, data->mlx_vars->mlx_window);
	mlx_destroy_image(data->mlx_vars->mlx_ptr,data->mlx_vars->mlx_image);
    data->mlx_vars->mlx_image = mlx_new_image(data->mlx_vars->mlx_ptr, W, H);
    data->mlx_vars->buffer = mlx_get_data_addr (data->mlx_vars->mlx_image, &data->mlx_vars->bpp, &data->mlx_vars->line_lenght, &data->mlx_vars->endian);
	updata_data(&data);
    drawing_minimap(data);
    mlx_put_image_to_window (data->mlx_vars->mlx_ptr, data->mlx_vars->mlx_window, data->mlx_vars->mlx_image, 0, 0);
}

int	move_player_press(int key, t_data *data)
{
	if (key == 53)
	{
		mlx_destroy_image (data->mlx_vars->mlx_ptr, data->mlx_vars->mlx_image);
		mlx_destroy_window (data->mlx_vars->mlx_ptr, data->mlx_vars->mlx_window);
		exit (0);
	}
	else if (key == S_KEY)
	{
		printf("DOWN\n");
		if (data->map[(int)(data->ply->x_pos + (sin(data->ply->rotation_angle) * data->ply->move_speed))][(int)(data->ply->y_pos)] != '1')
		{
			data->ply->x_pos_o += sin(data->ply->rotation_angle) * data->ply->move_speed;
			data->ply->y_pos_o += cos(data->ply->rotation_angle) * data->ply->move_speed;
		}

	}
	else if (key == W_KEY)
	{
		printf("UP\n");
		data->ply->x_pos_o -= sin(data->ply->rotation_angle) * data->ply->move_speed;
		data->ply->y_pos_o -= cos(data->ply->rotation_angle) * data->ply->move_speed;
	}
	else if (key == AROW_LEFT)
	{
		printf("A_KEY\n");
		data->ply->rotation_angle += data->ply->rotation_speed;
	}
	else if (key == AROW_RIGHT)
	{
		printf("D_KEY\n");
		data->ply->rotation_angle -= data->ply->rotation_speed;
	}
	else if (key == A_KEY)
	{
		printf("AROW_LEFT\n");
		data->ply->y_pos_o -= .54 * data->ply->move_speed;
		// data->ply->rotation_angle -= 0.231425;
	}
	else if (key == D_KEY)
	{
		printf("AROW_RIGHT\n");
		data->ply->y_pos_o += .54 * data->ply->move_speed;
		// data->ply->rotation_angle -= 0.231425;
	}
	// printf("next_x=%f, next_y=%f\n", data->ply->x_pos, data->ply->y_pos);
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