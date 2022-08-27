#include "../includes/cub3d.h"

void	draw__(t_data *data){
	data->mlx_vars = (t_mlx *)malloc(sizeof(t_mlx));
    if(!data->mlx_vars)
        ft_error();
    data->mlx_vars->mlx_ptr = mlx_init();
	if (data->mlx_vars->mlx_ptr == NULL)
		_error("MLX error");
    data->mlx_vars->mlx_window = mlx_new_window ( data->mlx_vars->mlx_ptr, W, H,"cub3d");
    data->mlx_vars->mlx_image = mlx_new_image(data->mlx_vars->mlx_ptr, W, H);
    data->mlx_vars->buffer = mlx_get_data_addr (data->mlx_vars->mlx_image, &data->mlx_vars->bpp, &data->mlx_vars->line_lenght, &data->mlx_vars->endian);
	draw_ceilling_floor(data);
	draw__map(data);
	draw__player(data);
	// draw__fov(data);
	draw__pov(data);
	// ray_caste(data);
    mlx_put_image_to_window (data->mlx_vars->mlx_ptr, data->mlx_vars->mlx_window, data->mlx_vars->mlx_image, 0, 0);
	mlx_hook(data->mlx_vars->mlx_window, KeyPress, KeyPressMask, kay_press, data);
	mlx_hook(data->mlx_vars->mlx_window, KeyRelease, KeyReleaseMask, kay_releass, data);
	mlx_hook (data->mlx_vars->mlx_window, 17, 1L << 0, close_cross, data);
	mlx_loop_hook(data->mlx_vars->mlx_ptr, looop__hooking, data);
    mlx_loop (data->mlx_vars->mlx_ptr);
}

void	re_draw__(t_data *data){
	mlx_clear_window(data->mlx_vars->mlx_ptr, data->mlx_vars->mlx_window);
	mlx_destroy_image(data->mlx_vars->mlx_ptr,data->mlx_vars->mlx_image);
    data->mlx_vars->mlx_image = mlx_new_image(data->mlx_vars->mlx_ptr, W, H);
    data->mlx_vars->buffer = mlx_get_data_addr (data->mlx_vars->mlx_image, &data->mlx_vars->bpp, &data->mlx_vars->line_lenght, &data->mlx_vars->endian);
    draw_ceilling_floor(data);
	draw__map(data);
	draw__player(data);
	// draw__fov(data);
	draw__pov(data);
	// ray_caste(data);
    mlx_put_image_to_window (data->mlx_vars->mlx_ptr, data->mlx_vars->mlx_window, data->mlx_vars->mlx_image, 0, 0);
}

int looop__hooking(t_data *data){
	player_update(&data);
	re_draw__(data);
	return (0);
}
//

int	close_cross(void *param)
{
	(void)param;
	exit (0);
}

int	kay_press(int key, t_data *data){

	if (key == 53)
	{
		mlx_destroy_image (data->mlx_vars->mlx_ptr, data->mlx_vars->mlx_image);
		mlx_destroy_window (data->mlx_vars->mlx_ptr, data->mlx_vars->mlx_window);
		exit (0);
	}
	else if (key == S_KEY)
		data->ply->walk_direction = -1;
	else if (key == W_KEY)
		data->ply->walk_direction = 1;
	else if (key == AROW_LEFT)
		data->ply->turn_direction = -1;
	else if (key == AROW_RIGHT)
		data->ply->turn_direction = 1;
	else if (key == A_KEY)
		data->mm = -1;
	else if (key == D_KEY)
		data->mm = +1;
	return (0);
}

int	kay_releass(int key, t_data *data){
	if (key == S_KEY || key == W_KEY)
			data->ply->walk_direction = 0;
	else if (key == AROW_LEFT || key == AROW_RIGHT)
		data->ply->turn_direction = 0;
	else if (key == A_KEY)
		data->mm = 0;
	else if (key == D_KEY)
		data->mm = 0;
	return (0);
}