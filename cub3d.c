#include "cub3d.h"


void    checkLeaks()
{
    printf("\033[0;31m----------------------------\n");
    system("leaks cub3D");
    printf("\n----------------------------\n\033[0m");
}

int init_data(t_data *data)
{
    data->map = NULL;
    data->start_map = 7;
    data->p = 0;
    return (0);
}

void    start_windows()
{
    void    *mlx;
    void    *win;
    // void    *img;
    char    *str;

    // int x = 500;
    // int y =  500;
    str = ft_strdup("Hello i'm mmasstou");

    mlx = mlx_init();
    win = mlx_new_window(mlx, W, H , "-&- Cub3D -&-");
    mlx_string_put(mlx, win, (W / 2) - (W * 0.06) , 10, 0x219ebc, str);
    // img = mlx_png_file_to_image(mlx, "utils/3d.png", &x, &y);
    // mlx_put_image_to_window(mlx, win, img, x, y);
    mlx_loop(mlx);
}

int main(int argc, char *argv[])
{
    t_data  data;

    (void)argc;
    // atexit(checkLeaks);
    checkargs(argc, argv);
    init_data(&data);
    parsing(argv, &data);
    start_windows();
    return (0);
}