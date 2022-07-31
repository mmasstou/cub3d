/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 18:39:23 by mmasstou          #+#    #+#             */
/*   Updated: 2022/07/31 20:46:19 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
void    parsing_map(char *argv[], t_data *data)
{
    
}
int get_map_size(int fd)
{
    int index;

    
}
void    parsing(char *argv[], t_data *data)
{
    int fd;
    char **g_map;

    fd = open(argv[1], O_RDONLY, 0777);
    if (fd == -1)
        exit (1);
    
    
    parsing_map(argv, data);
}