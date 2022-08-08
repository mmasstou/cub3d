/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellakr <abellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 16:51:54 by abellakr          #+#    #+#             */
/*   Updated: 2022/08/08 16:50:24 by abellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d.h"

void    graphic(t_data *data)
{
    data->mlx_vars = (t_mlx *)malloc(sizeof(t_mlx));

    data->mlx_vars->mlx_ptr = mlx_init();
    data->mlx_vars->mlx_window = mlx_new_window ( data->mlx_vars->mlx_ptr, W, H,"cub3d");
    data->mlx_vars->mlx_image = mlx_new_image(data->mlx_vars->mlx_ptr, W, H);
    data->mlx_vars->buffer = mlx_get_data_addr (data->mlx_vars->mlx_image, &data->mlx_vars->bpp, &data->mlx_vars->line_lenght, &data->mlx_vars->endian);
    draw_minimap(data);
    mlx_put_image_to_window (data->mlx_vars->mlx_ptr, data->mlx_vars->mlx_window, data->mlx_vars->mlx_image, 0, 0);
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
            my_mlx_pixel_put(j*10 , i *10, data, 16777215);
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