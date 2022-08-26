/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_params2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 07:22:41 by abellakr          #+#    #+#             */
/*   Updated: 2022/08/26 15:34:26 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

//----------------------------------------------
void	save_f(char **line, t_data *data)
{
	if (!ft_strncmp(line[0], "F", 1) && data->exit.f == 0)
	{
		save_color(line[0], line[1], data);
		data->exit.f++;
	}
	else if (!ft_strncmp(line[0], "F", 2) && data->exit.f == 1)
		ft_error();
}

//----------------------------------------------
void	save_c(char **line, t_data *data)
{
	if (!ft_strncmp(line[0], "C", 1) && data->exit.c == 0)
	{
		save_color(line[0], line[1], data);
		data->exit.c++;
	}
	else if (!ft_strncmp(line[0], "C", 2) && data->exit.c == 1)
		ft_error();
}

//------------------------------------------------------------------------
void	save_color(char *color, char *color_data, t_data *data)
{
	char	**color_tab;

	color_tab = ft_split(color_data, ',');
	check_color_validity(color_tab);
	if (ft_strncmp(color, "C", 1) == 0)
	{
		data->c.r = ft_atoi(color_tab[0]);
		data->c.g = ft_atoi(color_tab[1]);
		data->c.b = ft_atoi(color_tab[2]);
	}
	else if (ft_strncmp(color, "F", 1) == 0)
	{
		data->f.r = ft_atoi(color_tab[0]);
		data->f.g = ft_atoi(color_tab[1]);
		data->f.b = ft_atoi(color_tab[2]);
	}
	free_array(color_tab);
}

//--------------------------------------------------
void	check_color_validity(char **color_tab)
{
	int	r;
	int	g;
	int	b;

	if (color_tab[0] && color_tab[1] && color_tab[2])
	{
		r = ft_atoi(color_tab[0]);
		g = ft_atoi(color_tab[1]);
		b = ft_atoi(color_tab[2]);
	}
	check_color_digit(color_tab);
	if (array_size(color_tab) != 3 || r < 0 || g < 0 || \
	b < 0 || r > 255 || g > 255 || b > 255)
		ft_error();
}

//-------------------------------------------
void	check_color_digit(char **color_tab)
{
	int	i;
	int	j;

	i = 0;
	while (color_tab[i])
	{
		j = 0;
		while (color_tab[i][j])
		{
			if (ft_isdigit(color_tab[i][j]) == 0)
				ft_error();
			j++;
		}
		i++;
	}
}
