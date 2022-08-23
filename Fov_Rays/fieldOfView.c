#include "../cub3d.h"

double draw_ray(t_data *data, int x, int y, double ray_angle)
{
	int dx, dy, err, sx,sy,e2, x1, y1, player_x;;
	t_pos wall_col;
	float dest;
	x1 = x + (H * cos(ray_angle));
	y1 = y + (H * sin(ray_angle));
	player_x = x;
	dx = abs(x1 - x);
	dy = -abs(y1 - y);
	sx = x < x1 ? 1 : -1;
	sy = y < y1 ? 1 : -1;
	err = dx + dy;
	while (1)
	{
		my_mlx_pixel_put(x,y,data,data->ply->color);
		e2 = 2*err;
		if (e2 >= dy) 
		{ /* e_xy+e_x > 0 */
			if (x == x1) break;
			err += dy;
			x += sx;
	 	}
 		if (e2 <= dx) 
		{ /* e_xy+e_y < 0 */
 			if (y == y1) break;
 			err += dx;
			y += sy;
 		}
		if (wall_collaction(x / data->unit , y / data->unit, data) == 1)
			break;
		// printf("field_of_views > %d, %d\n", x / data->unit, y / data->unit);
	}
	wall_col.x = x / data->unit;
	wall_col.y = y / data->unit;
	dest = fabs(wall_col.x - player_x) / sin(data->ply->rotation_angle + ray_angle);
	return (fabs(dest));
}

void   field_of_views(float x1, float y1, double ray_angle, t_data *data){
		int h;
		double dest;
		double g;
		dest = draw_ray (
			data,
			x1,
			y1,
			ray_angle
		);
		// printf("wall dest :%f\n", dest);
}
