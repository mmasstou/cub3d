/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellakr <abellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 07:21:06 by abellakr          #+#    #+#             */
/*   Updated: 2022/09/08 12:42:55 by abellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

//-----------------------------------------------------
void	save_no(char **line, t_data *data)
{
	int i = 1;
	char *tmp1;
	char *tmp2;
	if (!ft_strncmp(line[0], "NO", 2) && data->exit.no == 0)
	{
		tmp1 = ft_strdup(line[i]);
		while(line[++i])
		{
			tmp2 = ft_strjoin(tmp1, " ");
			free(tmp1);
			tmp1 = ft_strjoin(tmp2, line[i]);
			free(tmp2);
		}
		data->no = ft_strdup(tmp1);
		free(tmp1);
		data->exit.no++;
	}
	else if (!ft_strncmp(line[0], "NO", 2) && data->exit.no == 1)
		ft_error ();
}

//-----------------------------------------------------
void	save_so(char **line, t_data *data)
{
	int i = 1;
	char *tmp1;
	char *tmp2;
	if (!ft_strncmp(line[0], "SO", 2) && data->exit.so == 0)
	{
		tmp1 = ft_strdup(line[i]);
		while(line[++i])
		{
			tmp2 = ft_strjoin(tmp1, " ");
			free(tmp1);
			tmp1 = ft_strjoin(tmp2, line[i]);
			free(tmp2);
		}
		data->so = ft_strdup(tmp1);
		free(tmp1);
		data->exit.so++;
	}
	else if (!ft_strncmp(line[0], "SO", 2) && data->exit.so == 1)
		ft_error ();
}

//-----------------------------------------------------
void	save_we(char **line, t_data *data)
{
	int i = 1;
	char *tmp1;
	char *tmp2;
	if (!ft_strncmp(line[0], "WE", 2) && data->exit.we == 0)
	{
		tmp1 = ft_strdup(line[i]);
		while(line[++i])
		{
			tmp2 = ft_strjoin(tmp1, " ");
			free(tmp1);
			tmp1 = ft_strjoin(tmp2, line[i]);
			free(tmp2);
		}
		data->we = ft_strdup(tmp1);
		free(tmp1);
		data->exit.we++;
	}
	else if (!ft_strncmp(line[0], "WE", 2) && data->exit.we == 1)
		ft_error ();
}

//-----------------------------------------------------
void	save_ea(char **line, t_data *data)
{
	int i = 1;
	char *tmp1;
	char *tmp2;
	if (!ft_strncmp(line[0], "EA", 2) && data->exit.ea == 0)
	{
		tmp1 = ft_strdup(line[i]);
		while(line[++i])
		{
			tmp2 = ft_strjoin(tmp1, " ");
			free(tmp1);
			tmp1 = ft_strjoin(tmp2, line[i]);
			free(tmp2);
		}
		data->ea = ft_strdup(tmp1);
		free(tmp1);
		data->exit.ea++;
	}
	else if (!ft_strncmp(line[0], "EA", 2) && data->exit.ea == 1)
		ft_error ();
}
