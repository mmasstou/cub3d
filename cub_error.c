#include "cub3d.h"

void    cub_error(char *title, char *msg, char *extra_msg)
{
    if (extra_msg == NULL)
        printf("\x1b[36mCub3D\033[0m %s:%s: %s%s\n", COLOR_FAILURE,title, msg, COLOR_END);
    else if (extra_msg != NULL)
        printf("\x1b[36mCub3D\033[0m %s:%s: %s: %s%s\n", COLOR_FAILURE,title, msg, extra_msg, COLOR_END);
    exit(1);
}
