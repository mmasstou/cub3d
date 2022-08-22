#include "../cub3d.h"

void   field_of_views(t_data *data){
    double o;

	o = 0.0;
	while (o < degreeto_radian(FOV) / 2)
	{
		draw_line(
		data,
		data->ply->x_pos,
		data->ply->y_pos,
		data->ply->x_pos + (90 * cos(data->ply->rotation_angle + o)),
		data->ply->y_pos + (90 * sin(data->ply->rotation_angle + o))
		);
		draw_line(
		data,
		data->ply->x_pos,
		data->ply->y_pos,
		data->ply->x_pos + (90 * cos(data->ply->rotation_angle - o)),
		data->ply->y_pos + (90 * sin(data->ply->rotation_angle - o))
		);
		o += .00013;
	}
}
