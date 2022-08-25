/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellakr <abellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 12:53:59 by mmasstou          #+#    #+#             */
/*   Updated: 2022/08/22 15:33:19 by abellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
// void trace(float x, float y, float radius, t_data *data);
void	rotation_y(float *x, float *z, float beta);
t_player	*init_player(t_player **p){
	(*p)->x_pos_o = 0;
	(*p)->y_pos_o = 0;
	(*p)->radius = 0;
	(*p)->turn_direction = 0;
	(*p)->walk_direction = 0;
	// printf("plpppp +> %c\n", (*p)->spawning_orientation);
	if ((*p)->spawning_orientation == 'N')
		(*p)->rotation_angle = 3 * M_PI_2;
	else if ((*p)->spawning_orientation == 'S')
		(*p)->rotation_angle = M_PI_2;
	else if ((*p)->spawning_orientation == 'E')
		(*p)->rotation_angle = 0;
	else if ((*p)->spawning_orientation == 'W')
		(*p)->rotation_angle = M_PI;
	(*p)->move_speed = 4;
	(*p)->rotation_speed = degreeto_radian(15);
	return (*p);
}


static void draw_pov(float x, float y, float des, t_data *data)
{
	float next_y;
	float next_x;

	next_y = y;
	next_x = x;
	next_y -= des;
	// rotation_y(&next_x, &next_y, data->ply->rotation_angle);
	// x += (int)(data->ply->ply_w / 2);
	x += data->ply->ply_w / 2;
	// printf("x = %f, next_x = %f\ny = %f, next_y = %f\n", x, next_x, y, next_y);
	while (x >= next_x)
	{
		while (y >= next_y)
		{
			row_dda(x, y, next_x, next_y, data);
			y --;
		}
		x--;
	}
}



static void    render_ply(float x, float y, t_data *data, int color)
{
	int index;
	int jndex;
	int next_x;
	int next_y;
	int i;
	int j;
	int unitx;
	int unity;

	(void)color;
	unitx = x;
	unity = y;
	index = (x + data->unit / 4);
	data->ply->ply_w = index;
	i = (y + data->unit / 4);
	j = y;
	while (x <= index)
	{
		jndex = i;
		y = j;
		while (y <= jndex)
		{
			if (x < index)
			{
				next_x = x + 1;
				row_dda(x, y, next_x, next_y, data);
			}
			if (y < jndex)
			{
				next_y = y + 1;
				row_dda(x, y, next_x, next_y, data);
			}
			y++;
		}
		x++;
	}
	draw_pov(unitx, unity, 40, data);
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
	// updata player position:
	printf("x=%f, y=%f\n", data->ply->x_pos, data->ply->y_pos);
	unitx = data->ply->y_pos * (data->unit) + (data->unit / 4);
	unity = data->ply->x_pos * (data->unit) + (data->unit / 4);
	rect_color = PLAYER;
	render_ply(unitx, unity, data, rect_color);
	
	return (0);
}

