#include "cub3d.h"

void    dda_func(t_data *vars)
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
    }
}

void	casting(int colid, double ray_angle, t_data *data){
	bool	is_ray_facing_down = ray_angle > 0 && ray_angle < M_PI;
	bool	is_ray_facing_up = !is_ray_facing_down;
	bool	is_ray_facing_right = ray_angle < M_PI_2 || ray_angle > 3 * M_PI_2;
	bool	is_ray_facing_left = !is_ray_facing_right;
	float x_intercept;
	float y_intercept;
	float x__step;
	float y__step;
	float next__horizontal_intx;
	float next__horizontal_inty;
	printf("ray_angle %f\n",ray_angle);
	printf("is_ray_facing_down %d\n",is_ray_facing_down);
	return ;
	//  --&-- horizontal --&--
	bool found__horizontal_wallhit = false;
	float wall_hit__x = 0;
	float wall_hit__y = 0;
	// find y-coordinate of closest horizontal grid intersection
	y_intercept = floor(data->ply->y_pos / data->unit) * data->unit;
	y_intercept +=  is_ray_facing_down ? data->unit: 0;
	// find x-coordinate of closest horizontal grid intersection
	x_intercept = data->ply->x_pos + (y_intercept - data->ply->y_pos) / tan(ray_angle);
	//  catculate increment of x__step and y__step
	y__step = data->unit;
	y__step *= is_ray_facing_up ? -1:1;
	x__step = data->unit / tan(ray_angle);
	x__step *= (is_ray_facing_left && x__step > 0)  ? -1 : 1;
	x__step *= (is_ray_facing_right && x__step < 0)  ? -1 : 1;
	next__horizontal_intx = x_intercept;
	next__horizontal_inty = y_intercept;
	if (is_ray_facing_up)
		next__horizontal_inty --;
	// start increment x__step until find wall
	printf("init x__step = %f\n", x__step);
	printf("init y__step = %f\n", y__step);
	printf("init next__horizontal_intx = %f\n", next__horizontal_intx);
	printf("init next__horizontal_inty = %f\n", next__horizontal_inty);
	while (next__horizontal_intx >= 0 && next__horizontal_intx <= H && next__horizontal_inty >= 0 && next__horizontal_inty <= W){
		printf("next__horizontal_intx = %f, next__horizontal_inty = %f\n", next__horizontal_intx, next__horizontal_inty);
		if (wall_collaction(next__horizontal_intx, next__horizontal_inty, data) != 0){
			//  we found a wall
			found__horizontal_wallhit = true;
			wall_hit__x = next__horizontal_intx;
			wall_hit__y = next__horizontal_inty;
			printf("wall_hit__x = %f, wall_hit__y = %f\n", wall_hit__x, wall_hit__y);
			// 
			data->x1 = data->ply->x_pos * data->unit;
			data->y1 = data->ply->y_pos * data->unit;
			data->x2 = (data->ply->x_pos * data->unit) + next__horizontal_intx;
			data->y2 = (data->ply->y_pos * data->unit) + next__horizontal_inty;
			data->ply->color = 1046797;
			// printf("next__horizontal_inty = %f, next__horizontal_intx = %f\n", next__horizontal_inty, next__horizontal_intx);
			// dda_func(
			// 	data
			// );
			break;
		}else{
			// printf("next step[%f,%f]\nx = %f, y = %f\n",x__step, y__step, next__horizontal_intx, next__horizontal_inty);
			next__horizontal_intx += x__step;
			next__horizontal_inty += y__step;
		}
	}
}

void    draw___ray(t_data *vars, float x1, float y1, float x2, float y2)
{
    float    steps;
    float    dx;
    float    dy;

    dx = x2 - x1;
    dy = y2 - y1;
    if (fabsf(dx) > fabsf(dy))
        steps = fabsf(dx);
    else
        steps = fabsf(dy);
    dx /= steps;
    dy /= steps;
    while ((int)(x1 - x2) || (int)(y1 - y2))
    {
        my_mlx_pixel_put(x1 , y1 , vars, vars->ply->color);
        x1 += dx;
        y1 += dy;
    }
}

int ray_caste(t_data *data){
	int colid;
	double ray_angle;
	float player__x;
	float player__y;

	player__x = data->ply->x_pos * data->unit;
	player__y = data->ply->y_pos * data->unit;
	ray_angle = data->ply->rotation_angle - FOV / 2;
	// normalize_angle(&ray_angle);
	colid = 0;
	while (colid < NBR_RAYS){
		// printf("col Id = %d\n", colid);
		// printf("ray_angle = %f\n", ray_angle);
		casting(colid, ray_angle, data);
		// draw___ray(
		// 	data,
		// 	player__x,
		// 	player__y,
		// 	player__x  + (cos(ray_angle) * 60),
		// 	player__y + (sin(ray_angle) * 60)
		// );
		ray_angle += FOV_INC; 
		colid ++;
	}
	return (0);
}