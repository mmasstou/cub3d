#include "../cub3d.h"

int	move_player_press(int key, t_data *data)
{
	if (key == 53)
	{
		mlx_destroy_image (data->mlx_vars->mlx_ptr, data->mlx_vars->mlx_image);
		mlx_destroy_window (data->mlx_vars->mlx_ptr, data->mlx_vars->mlx_window);
		exit (0);
	}
	else if (key == S_KEY || key == 125)
	{
		printf("DOWN\n");
		data->ply->x_pos_o += cos(data->ply->rotation_angle) * data->ply->move_speed;
		data->ply->y_pos_o += sin(data->ply->rotation_angle) * data->ply->move_speed;

	}
	else if (key == W_KEY || key == 126)
	{
		printf("UP\n");

		data->ply->x_pos_o -= cos(data->ply->rotation_angle) * data->ply->move_speed;
		data->ply->y_pos_o -= sin(data->ply->rotation_angle) * data->ply->move_speed;
	}
	else if (key == A_KEY || key == 123)
	{
		printf("LEFT\n");
		data->ply->turn_direction += 1;
		// data->ply->rotation_angle += 0.231425;
	}
	else if (key == D_KEY || key == 124)
	{
		printf("RIGHT\n");
		data->ply->turn_direction -= 1;
		// data->ply->rotation_angle -= 0.231425;
	}
	printf("next_x=%f, next_y=%f\n", data->ply->x_pos, data->ply->y_pos);

	re_draw(data);
	return (0);
}