/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 12:53:59 by mmasstou          #+#    #+#             */
/*   Updated: 2022/08/18 05:11:42 by mmasstou         ###   ########.fr       */
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
	p->rotation_angle = M_PI_2;
	p->move_speed = 4;
	p->rotation_speed = 2 * (M_PI / 180);
	return (p);
}


static void draw_pov(float x, float y, t_data *data)
{
	float next_x;
	float next_y;
	
	next_x = x;
	next_y = y;
	next_x += cos(data->ply->rotation_angle) * 30;
	next_y += sin(data->ply->rotation_angle) * 30;
	// printf("x = %f, next_x = %f\ny = %f, next_y = %f\n", x, next_x, y, next_y);
	row_dda(x, y, next_x, next_y, data);
}
static void    render_ply(float x, float y, t_data *data, int color)
{
	int index;
	int jndex;
	int i;
	int j;

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
}
void	update_turn_angle(t_data **data)
{
	(*data)->ply->rotation_angle += (*data)->ply->turn_direction * (*data)->ply->rotation_speed;
	printf("rotation_angle = %f\n", (*data)->ply->rotation_angle);
}

void	update_player_pos(int *x, int *y, t_data *data)
{
	float move_step;

	move_step = data->ply->walk_direction * data->ply->move_speed;
	*x += move_step * cos(data->ply->rotation_angle);
	*y += move_step * sin(data->ply->rotation_angle);
	printf("player +> (%d, %d)\n", *x, *y);
}


int	drawing_player(t_data	*data){
	int unitx;
	int unity;
	int rect_color;
	int i;

	unitx = data->ply->y_pos * (data->unit) + (data->unit / 4);
	unity = data->ply->x_pos * (data->unit) + (data->unit / 4);
	update_player_pos(&unitx, &unity, data);
	update_turn_angle(&data);
	i = data->ply->radius;
	rect_color = PLAYER;
	render_ply(unitx, unity, data, rect_color);
	draw_pov(unitx, unity, data);
	return (0);
}

