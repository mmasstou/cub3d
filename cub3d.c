#include "cub3d.h"


void    checkLiks()
{
    printf("\033[0;31m----------------------------\n");
    system("leaks cub3D");
    printf("\n----------------------------\n\033[0m");
    // printf("%s", COLOR_SUCCESS);
    // system("leaks cub3D");
}

void    free_cub3d_data(t_data *data)
{
    free(data->ea);
    free(data->no);
    free(data->so);
    free(data->we);
    data = NULL;
}

int main(int argc, char *argv[])
{
    t_data    data;
    // void *mlx;

    atexit(checkLiks);
    
    checkargs(argc, argv, &data);
	// mlx = mlx_init();
	// void *win = mlx_new_window(mlx, W, H, "Wolfenstein 3D -* Cub3d *-");
	// mlx_string_put(mlx, win, 10, 10, 0xFFFFFF, "Hello World");
	// mlx_loop(mlx);
    printf("NO -- %s\n",data.no);
    printf("EA -- %s\n",data.ea);
    printf("SO -- %s\n",data.so);
    printf("WE -- %s\n",data.we);
    printf("--- F -- \nR:%d\nG:%d\nB:%d\n",data.f.r, data.f.g, data.f.b);
    printf("--- C -- \nR:%d\nG:%d\nB:%d\n",data.c.r, data.c.g, data.c.b);
    free(data.map);
    free_cub3d_data(&data);
    return (0);
}