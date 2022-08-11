/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellakr <abellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 16:51:54 by abellakr          #+#    #+#             */
/*   Updated: 2022/08/11 15:36:13 by abellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d.h"

void    graphic(t_data *data)
{
    data->mlx_vars = (t_mlx *)malloc(sizeof(t_mlx));
    if(!data->mlx_vars)
        ft_error();
    data->mlx_vars->mlx_ptr = mlx_init();
    data->mlx_vars->mlx_window = mlx_new_window ( data->mlx_vars->mlx_ptr, W, H,"cub3d");
    data->mlx_vars->mlx_image = mlx_new_image(data->mlx_vars->mlx_ptr, W, H);
    data->mlx_vars->buffer = mlx_get_data_addr (data->mlx_vars->mlx_image, &data->mlx_vars->bpp, &data->mlx_vars->line_lenght, &data->mlx_vars->endian);
    draw_minimap(data);
    mlx_put_image_to_window (data->mlx_vars->mlx_ptr, data->mlx_vars->mlx_window, data->mlx_vars->mlx_image, 0, 0);
    mlx_hook (data->mlx_vars->mlx_window, 2, 1L << 0, esc, data);
	mlx_hook (data->mlx_vars->mlx_window, 17, 1L << 0, close_cross, data);
    mlx_loop (data->mlx_vars->mlx_ptr);
}
//-------------------------------------------------
void	draw_minimap(t_data *data)
{
    int i;
    int j;

    i = 0;
    while(data->map[i])
    {
        j = 0;
        while(data->map[i][j] != '\0' && data->map[i][j] != '\n')
        {
            if(data->map[i][j] == '1') // white
                draw_rec(j * 20, i * 20, data, 16777215);
            else if (data->map[i][j] == '0')
                draw_rec(j * 20, i * 20, data, 255); 
            else if (data->map[i][j] == 'N' || data->map[i][j] == 'W' || data->map[i][j] == 'S' || data->map[i][j] == 'E' )// yellow
                draw_rec(j * 20, i * 20, data, 16777045);
            else if (data->map[i][j] == ' ') // red
                draw_rec(j * 20, i * 20, data, 0);
            
            j++;
        }
        i++;
    }
}
/*------------------------------------------------------------------*/
void	my_mlx_pixel_put(int x, int y, t_data *data, int color)
{
	char	*dst;

	if ((x >= 0 && x < W) && (y >= 0 && y < H))
	{
		dst = data->mlx_vars->buffer + (y * data->mlx_vars->line_lenght + x * (data->mlx_vars->bpp / 8));
		*(unsigned int *)dst = color;
	}
}
//---------------------------------------------------------- draw rec
void    draw_rec(int x, int y, t_data *data, int color)
{
    int	i;
	int j;

	i = y;
	while (i <= y + 18)
	{
		j = x;
		while (j <= x + 18)
        {
			my_mlx_pixel_put(j, i, data, color);
            j++;
        }
		i++;
	}
}
/*----------------------------------------------------------------*/
int	esc(int keycode, t_data *data)
{
	if (keycode == 53)
	{
		mlx_destroy_image (data->mlx_vars->mlx_ptr, data->mlx_vars->mlx_image);
		mlx_destroy_window (data->mlx_vars->mlx_ptr, data->mlx_vars->mlx_window);
		exit (0);
	}
	return (0);
}

/*----------------------------------------------------------------*/
int	close_cross(void *param)
{
	(void)param;
	exit (0);
}