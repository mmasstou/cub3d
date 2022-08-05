/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkargs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 11:24:59 by mmasstou          #+#    #+#             */
/*   Updated: 2022/08/05 11:25:00 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void     checkargs(int argc, char *argv[])
{
    char    *map_name;
    int     fd;

    if (argc  != 2)
        _error("argument required");
    map_name = ft_strrchr(argv[1], '.');
    if ((map_name && ft_strcmp(map_name, ".cub") != 0) || !map_name)
    {   
        _error("Map in format *.cub required ");
    }
    fd = open(argv[1], O_RDONLY, 0777);
    if (fd == -1)
         _error("Can`t Open Map");
    else
        close(fd);
}