#include "../cub3d.h"

int ft_rgb(int t, int r, int g, int b)
{
    return ((t << 24) + (r << 16) + (g << 8) + b);
}