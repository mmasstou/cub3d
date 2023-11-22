/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 07:21:06 by abellakr          #+#    #+#             */
/*   Updated: 2022/08/26 15:34:26 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

//-----------------------------------------------------
void	save_no(char **line, t_data *data)
{
	if (!ft_strncmp(line[0], "NO", 2) && data->exit.no == 0)
	{
		data->no = ft_strdup(line[1]);
		data->exit.no++;
	}
	else if (!ft_strncmp(line[0], "NO", 2) && data->exit.no == 1)
		_error(NULL);
}

//-----------------------------------------------------
void	save_so(char **line, t_data *data)
{
	if (!ft_strncmp(line[0], "SO", 2) && data->exit.so == 0)
	{
		data->so = ft_strdup(line[1]);
		data->exit.so++;
	}
	else if (!ft_strncmp(line[0], "SO", 2) && data->exit.so == 1)
		_error(NULL);
}

//-----------------------------------------------------
void	save_we(char **line, t_data *data)
{
	if (!ft_strncmp(line[0], "WE", 2) && data->exit.we == 0)
	{
		data->we = ft_strdup(line[1]);
		data->exit.we++;
	}
	else if (!ft_strncmp(line[0], "WE", 2) && data->exit.we == 1)
		_error(NULL);
}

//-----------------------------------------------------
void	save_ea(char **line, t_data *data)
{
	if (!ft_strncmp(line[0], "EA", 2) && data->exit.ea == 0)
	{
		data->ea = ft_strdup(line[1]);
		data->exit.ea++;
	}
	else if (!ft_strncmp(line[0], "EA", 2) && data->exit.ea == 1)
		_error(NULL);
}
