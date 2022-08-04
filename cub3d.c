#include "cub3d.h"


void    checkLeaks()
{
    printf("\033[0;31m----------------------------\n");
    system("leaks cub3D");
    printf("\n----------------------------\n\033[0m");
}


int main(int argc, char *argv[])
{
    t_data  data;

    parsing(argv, &data);
    printf("NO %s\n", data.no);
    printf("SO %s\n", data.so);
    printf("WE %s\n", data.we);
    printf("EA %s\n", data.ea);
    printf("F %d,%d,%d\n", data.f.r, data.f.g, data.f.b);
    printf("C %d,%d,%d\n", data.c.r, data.c.g, data.c.b);
    free_params(&data);
    atexit(checkLeaks);  
    return (0);
}