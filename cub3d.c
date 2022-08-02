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

    (void)argc;
    atexit(checkLeaks);
    checkargs(argc, argv);
    data.start_map = 7;
    data.p = 0;
    parsing(argv, &data);
    return (0);
}