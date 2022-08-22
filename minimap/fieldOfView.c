#include "../cub3d.h"

void   field_of_views(float x1, float y1, t_data *data){
    double o;

	o = 0.0;
	while (o < degreeto_radian(FOV) / 2)
	{
		draw_line(
		data,
		x1,
		y1,
		x1 + (90 * cos(data->ply->rotation_angle + o)),
		y1 + (90 * sin(data->ply->rotation_angle + o))
		);
		draw_line(
		data,
		x1,
		y1,
		x1 + (90 * cos(data->ply->rotation_angle - o)),
		y1 + (90 * sin(data->ply->rotation_angle - o))
		);
		o += .00013; 

	}
	printf("degreeto_radian(%d / %d) = |%f|\n", FOV, H, degreeto_radian(FOV / H));
}
