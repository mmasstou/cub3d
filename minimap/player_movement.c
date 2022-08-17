/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 12:53:59 by mmasstou          #+#    #+#             */
/*   Updated: 2022/08/17 22:34:04 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
// void trace(float x, float y, float radius, t_data *data);

t_player	*init_player(t_data *data){
	t_player *p;

	(void)data;
	p = (t_player *)malloc(sizeof(t_player));
	if (!p)
		exit(1);
	p->x_pos = 0;
	p->y_pos = 0;
	p->radius = 0;
	p->turn_direction = 0;
	p->walk_direction = 0;
	p->rotation_angle = 0;
	p->move_speed = 3;
	p->rotation_speed = 4 * (M_PI / 180);
	return (p);
}
int	row_dda(float x, float y, float next_x, float next_y, t_data *data)
{
	int		step;
	float	xinc;
	float	yinc;
	float	i;
	float	j;
	
	data->deltax = next_x - x;
	data->deltay = next_y - y;
	if (abs(data->deltax) > abs(data->deltay))
		step = abs(data->deltax);
	else
		step = abs(data->deltay);
	xinc = data->deltax / step;
	yinc = data->deltax / step;
	i = x;
	j = y;
	while (step >= 0)
	{
		my_mlx_pixel_put(i, j ,data, 15797260);
		i += xinc;
		j += yinc;
		step--;
	}
	return (0);
}
static void row_deriction(float x, float y, t_data *data)
{
	float next_x;
	float next_y;
	
	next_x = x;
	next_y = y;
	next_x += cos(data->ply->rotation_angle) * 30;
	next_y += sin(data->ply->rotation_angle) * 30;
	printf("rotation_angle = %f\n", data->ply->rotation_angle);
	// printf("x = %f, next_x = %f\ny = %f, next_y = %f\n", x, next_x, y, next_y);
	row_dda(x, y, next_x, next_y, data);
}
static void    render_ply(float x, float y, t_data *data, int color)
{
	int index;
	int jndex;
	int i;
	int j;
	int unitx;
	int unity;
	
	float move_step;
	move_step = data->ply->walk_direction * data->ply->move_speed;
	printf(">>move_step |%f\n", move_step);
	y = y + move_step * cos(data->ply->rotation_angle);
	x =  x + move_step * sin(data->ply->rotation_angle);
	unitx = x;
	unity = y;
	printf("x = %f\ny = %f\n",  x,  y);
	index = (x + data->unit / 4);
	i = (y + data->unit / 4); 
	j = y;
	
	while (x <= index)
	{
		jndex = i;
		y = j;
		while (y <= jndex)
		{
			my_mlx_pixel_put(x, y, data, color);
			y++;
		}
		x++;
	}
	row_deriction(unitx, unity, data);
}

int	drawing_player(t_data	*data){
	int unitx;
	int unity;
	int rect_color;
	int i;

	// unitx = data->ply->y_pos * data->unit;
	// unitx = unitx + (data->ply->radius / 2);
	// unity = data->ply->x_pos * data->unit;
	// unity = unity + (data->ply->radius / 2);	

	unitx = data->ply->y_pos * (data->unit) + (data->unit / 4);
	unity = data->ply->x_pos * (data->unit) + (data->unit / 4);
	// unitx = ((data->unit / 2) + (data->ply->y_pos * data->unit)) - ((data->ply->y_pos + data->ply->radius) / 2);
	// unity = ((data->unit / 2) + (data->ply->x_pos * data->unit)) - ((data->ply->x_pos + data->ply->radius) / 2);
	i = data->ply->radius;
	rect_color = PLAYER;

	render_ply(unitx, unity, data, rect_color);
	return (0);
}

// void trace(float x, float y, float radius, t_data *data) 
// { 
// 	float theta = 0;
// 	float xn;
// 	float yn;

// 	while (theta < 6.28)
// 	{
// 		xn = x + radius * cos(theta);
// 		yn = y + radius * sin(theta);

// 		theta += 3.14 / 180.0;
// 	}
// }
