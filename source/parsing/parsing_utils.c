/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 07:29:05 by abellakr          #+#    #+#             */
/*   Updated: 2022/08/26 15:34:26 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

//--------------------------- function that count array size
int	array_size(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	return (i);
}

//---------------------- function to free 2d array
void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (array[i] != NULL)
			free (array[i]);
		i++;
	}
	if (array)
		free (array);
}

//--------------------------------------- free data params
void	free_params(t_data *data)
{
	free (data->no);
	free (data->so);
	free (data->we);
	free (data->ea);
}

//-------------------------------------------- error function
void	ft_error(void)
{
	printf ("Error\n");
	exit (1);
}
