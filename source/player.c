#include "../includes/cub3d.h"

double degreeto_radian(float angle){
	return (angle *  (M_PI / 180));
}
int ft_rgb(int t, int r, int g, int b)
{
    return ((((t * 255) / 100) << 24) + (r << 16) + (g << 8) + b);
}

t_player	*init_player(t_player **p){
	(*p)->x_pos_o = 0;
	(*p)->y_pos_o = 0;
	(*p)->radius = 0;
	(*p)->turn_direction = 0;
	(*p)->walk_direction = 0;
	printf("player orientation +> %c\n", (*p)->spawning_orientation);
	if ((*p)->spawning_orientation == 'N')
		(*p)->rotation_angle = 3 * M_PI_2;
	else if ((*p)->spawning_orientation == 'S')
		(*p)->rotation_angle = M_PI_2;
	else if ((*p)->spawning_orientation == 'E')
		(*p)->rotation_angle = 0;
	else if ((*p)->spawning_orientation == 'W')
		(*p)->rotation_angle = M_PI;
	(*p)->move_speed = 0.04;
	(*p)->rotation_speed = degreeto_radian(1.5);
	return (*p);
}
void    draw__ray(t_data *vars)
{
    float    steps;
    float    dx;
    float    dy;

    dx = vars->x2 - vars->x1;
    dy = vars->y2 - vars->y1;
    if (fabsf(dx) > fabsf(dy))
        steps = fabsf(dx);
    else
        steps = fabsf(dy);
    dx /= steps;
    dy /= steps;
    while ((int)(vars->x1 - vars->x2) || (int)(vars->y1 - vars->y2))
    {
        my_mlx_pixel_put(vars->x1 , vars->y1 , vars, vars->ply->color);
        vars->x1 += dx;
        vars->y1 += dy;
		if (wall_collaction(vars->x1 / vars->unit , vars->y1 / vars->unit, vars) == 1)
			break;
    }
}
void	draw__fov(t_data *data){
	float p__x;
	int index;
	float p__y;
	double	ray__angle;
	float m;

	p__x = data->ply->x_pos * data->unit;
	p__y = data->ply->y_pos * data->unit;
	ray__angle = data->ply->rotation_angle - FOV / 2;
	index = 0;
	while (index < NBR_RAYS){
		// start
		data->x1 = p__x;
		data->y1 = p__y;
		data->x2 = p__x + (90 * cos(ray__angle));
		data->y2 = p__y + (90 * sin(ray__angle));
		data->ply->color = ft_rgb(20, X__COLOR);
		// end
		draw__ray(
			data
		);
		ray__angle += FOV / NBR_RAYS;
		index ++;
	}


}
void	draw__pov(t_data *data){
	int x1, y1;

	x1 = data->ply->x_pos * data->unit;
	y1 = data->ply->y_pos * data->unit;
	data->x1 = x1;
	data->y1 = y1;
	data->x2 = x1 + (20 * cos(data->ply->rotation_angle));
	data->y2 = y1 + (20 * sin(data->ply->rotation_angle));
	data->ply->color = ft_rgb(12, FOV_COLOR);
	dda_function(
		data
	);
}
void	draw__player(t_data *data){
	double ray_angle;
	int x1, y1;
	float player_unit;
	player_updata(&data);
	// printf(" OLD player Pos %f, %f\n", data->ply->x_pos, data->ply->y_pos);
	x1 = data->ply->x_pos * data->unit;
	y1 = data->ply->y_pos * data->unit;
	// x1 += data->unit / 2;
	// y1 += data->unit / 2;
	// player_unit = 1;
	// x1 -= player_unit / 2;
	// y1 -= player_unit / 2;
	// printf("player Pos %f, %f\n", data->ply->x_pos, data->ply->y_pos);
	
	render_player(
		data, 
		x1,
		y1, 
		WALL
		);
}
void	render_player(t_data *data, float x, float y, int color){
	float i;
	float j;
	int unit;
	int unity;

	unit = 1;
	i = x + unit;
	j = y + unit;
	unity = y;
	while (x <= i)
	{
		y = unity;
		while (y <= j)
		{
			my_mlx_pixel_put(x, y, data, color);
			y++;
		}
		x++;
	}
}
void normalize_angle(double *angle){
	*angle = (int)*angle % (int)(2 * M_PI);
	if (angle < 0)
		*angle =  *angle * (2 * M_PI);
}

void	player_updata(t_data **data){
	float step;
	float newPlayerx;
	float newPlayery;

	step = (*data)->ply->walk_direction * (*data)->ply->move_speed;
	(*data)->ply->rotation_angle += ((*data)->ply->turn_direction * (*data)->ply->rotation_speed);
	newPlayerx = (*data)->ply->x_pos + (cos((*data)->ply->rotation_angle) * step);
	newPlayery = (*data)->ply->y_pos + (sin((*data)->ply->rotation_angle) * step);
	if (wall_collaction(newPlayerx, newPlayery, *data) != 1)
	{
		(*data)->ply->x_pos = newPlayerx;
		(*data)->ply->y_pos = newPlayery;
	}
}

void    dda_function(t_data *vars)
{
    float    steps;
    float    dx;
    float    dy;

    dx = vars->x2 - vars->x1;
    dy = vars->y2 - vars->y1;
    if (fabsf(dx) > fabsf(dy))
        steps = fabsf(dx);
    else
        steps = fabsf(dy);
    dx /= steps;
    dy /= steps;
    while ((int)(vars->x1 - vars->x2) || (int)(vars->y1 - vars->y2))
    {
        my_mlx_pixel_put(vars->x1 , vars->y1 , vars, vars->ply->color);
        vars->x1 += dx;
        vars->y1 += dy;
		if (wall_collaction(vars->x1 / vars->unit , vars->y1 / vars->unit, vars) == 1)
			break;
    }
}