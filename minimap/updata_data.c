#include "../cub3d.h"

void    updata_data(t_data **data)
{
    int tmp;

    // printf("x = %d, y = %d\n", (*data)->ply->x_pos, (*data)->ply->y_pos);
    tmp = ((*data)->ply->x_pos * cos((*data)->ply->rotation_angle) - (*data)->ply->y_pos * sin((*data)->ply->rotation_angle));
    (*data)->ply->x_pos = ((*data)->ply->x_pos * sin((*data)->ply->rotation_angle) + (*data)->ply->y_pos * cos((*data)->ply->rotation_angle));
    (*data)->ply->y_pos = tmp;
    // printf("new_x = %d, new_y = %d\n", (*data)->ply->x_pos, (*data)->ply->y_pos);
}