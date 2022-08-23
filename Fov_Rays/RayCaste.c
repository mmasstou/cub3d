/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RayCaste.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 21:38:03 by mmasstou          #+#    #+#             */
/*   Updated: 2022/08/23 18:50:44 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void normalize_angle(double *angle){
	*angle = (int)*angle % (int)(2 * M_PI);
	if (angle < 0)
		*angle =  *angle * (2 * M_PI);
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
	// printf("is_ray_facing_right %d\n",is_ray_facing_right);
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
	// printf("init x__step = %f\n", x__step);
	// printf("init y__step = %f\n", y__step);
	// printf("init next__horizontal_intx = %f\n", next__horizontal_intx);
	// printf("init next__horizontal_inty = %f\n", next__horizontal_inty);
	while (next__horizontal_intx >= 0 && next__horizontal_intx <= W && next__horizontal_inty >= 0 && next__horizontal_inty <= H){
		printf("next__horizontal_intx = %f, next__horizontal_inty = %f\n", next__horizontal_intx, next__horizontal_inty);
		if (wall_collaction(next__horizontal_intx, next__horizontal_inty, data) != 0){
			//  we found a wall
			found__horizontal_wallhit = true;
			wall_hit__x = next__horizontal_intx;
			wall_hit__y = next__horizontal_inty;
			// 
			data->x1 = data->ply->x_pos * data->unit;
			data->y1 = data->ply->y_pos * data->unit;
			data->x2 = next__horizontal_intx;
			data->y2 = next__horizontal_inty;
			data->ply->color = 1046797;
			printf("next__horizontal_inty = %f, next__horizontal_intx = %f\n", next__horizontal_inty, next__horizontal_intx);
			dda_function(
				data
			);
			break;
		}else{
			printf("next step[%f,%f]\nx = %f, y = %f\n",x__step, y__step, next__horizontal_intx, next__horizontal_inty);
			next__horizontal_intx += x__step;
			next__horizontal_inty += y__step;
		}
	}
}
int ray_caste(t_data *data){
	int colid;
	double ray_angle;
	float wall_hitx;
	float wall_hity;
	float distence;

	wall_hitx = 0;
	wall_hity = 0;
	distence = 0;
	ray_angle = data->ply->rotation_angle - (FOV / 2);
	normalize_angle(&ray_angle);
	colid = 0;
	while (colid < NBR_RAYS){
		casting(colid, ray_angle, data);
		ray_angle += FOV / NBR_RAYS; 
		colid ++;
	}
	return (0);
}