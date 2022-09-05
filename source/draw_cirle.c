
#include "../includes/cub3d.h"
void    dda_circle(double x1, double y1,double x2, double y2,t_data *vars)
{
    double    steps;
    double    dx;
    double    dy;

    dx = x2 - x1;
    dy = y2 - y1;
    if (fabs(dx) > fabs(dy))
        steps = fabs(dx);
    else
        steps = fabs(dy);
    dx /= steps;
    dy /= steps;
    while ((int)(x1 - x2) || (int)(y1 - y2))
    {
        my_mlx_pixel_put(x1 , y1 , vars, vars->color_circle);
        x1 += dx;
        y1 += dy;
    }
}

void	draw__fov_redi(t_data *data, int x, int y, double angle)
{
	t_rays *tmp;
	
	tmp = data->rays;
	while (tmp)
	{
		data->ply->color = ft_rgb(40, FOV_COLOR);
		draw_line(
			data,
			x,
			y,
			x + cos(angle) * 50,
			y + sin(angle) * 50
		);
		tmp = tmp->next;
	}
}

void plotCircle(int xm, int ym, int r, t_data *data)
{
	int x = -r, y = 0, err = 2-2*r; /* bottom left to top right */
	do {
		my_mlx_pixel_put(xm-x, ym+y, data, 0); /* I. Quadrant +x +y */
		my_mlx_pixel_put(xm-y, ym-x, data, 0); /* II. Quadrant -x +y */
		my_mlx_pixel_put(xm+x, ym-y, data, 0); /* III. Quadrant -x -y */
		my_mlx_pixel_put(xm+y, ym+x, data, 0); /* IV. Quadrant +x -y */
		r = err;
		if (r <= y) 
			err += ++y*2+1; /* e_xy+e_y < 0 */
		if (r > x || err > y) /* e_xy+e_x > 0 or no 2nd y-step */
		err += ++x*2+1; /* -> x-step now */
	} while (x < 0);
	my_mlx_pixel_put(xm, ym, data, 0);
	draw__fov_redi(data, xm, ym, data->ply->rotation_angle);
}