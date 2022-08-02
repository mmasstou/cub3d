/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellakr <abellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 07:29:05 by abellakr          #+#    #+#             */
/*   Updated: 2022/08/02 09:31:20 by abellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

//--------------------------- function that count array size
int array_size(char **tab)
{
	int i;

	i = 0;
	while(tab[i] != NULL)
		i++;
	return (i);
}
//------------------------------------------------- function to free 2d array
void free_array(char **array)
{
    int i;

    i = 0;
    while(array[i])
    {
        if(array[i] != NULL)
            free(array[i]);
        i++;
    }
    if(array)
        free(array);
}