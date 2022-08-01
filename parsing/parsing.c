/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellakr <abellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 18:39:23 by mmasstou          #+#    #+#             */
/*   Updated: 2022/08/01 15:38:26 by abellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	*ft_reassign(void *oldptr, void *newptr)
{
	free(oldptr);
	return (newptr);
}

void    parsing_map(char **g_map, t_data *data, int g_map_size)
{
	int index;
	int jndex;
	
	(void)data;
	index = 0;
	// printf("g_map_size : %d\n", g_map_size);
	while (g_map[index])
	{
		// g_map[index] = ft_reassign(g_map[index], ft_strtrim(g_map[index], " "));
		if (ft_strncmp("NO", g_map[index],2) != 0 &&
			ft_strncmp("SO", g_map[index], 2) != 0 &&
			ft_strncmp("WE", g_map[index], 2) != 0 &&
			ft_strncmp("EA", g_map[index], 2) != 0 &&
			ft_strncmp("F", g_map[index], 1) != 0 &&
			ft_strncmp("C", g_map[index], 1) != 0 &&
			g_map[index][0] != '\n')
		{
			printf("line[%2d] : |%s", index, g_map[index]);
			// check map errors
			jndex = 0;
			while (g_map[index][jndex] != '\0' && g_map[index][jndex] != '\n')
			{
				// printf("|%c| -- |%c|\n", g_map[index][jndex], g_map[index][jndex + 1]);
				if (
					g_map[index][jndex] == 32 &&
					(((g_map[index][jndex + 1] && g_map[index][jndex + 1] == '0') || (g_map[index][jndex - 1] && g_map[index][jndex - 1] == '0')) ||
					((g_map[index - 1][jndex + 1] && g_map[index - 1][jndex + 1] == '0') || (g_map[index - 1][jndex - 1] && g_map[index - 1][jndex - 1] == '0'))
					)
					)
				{
					printf("Map Error\n1->|%c|->|%c|\n", g_map[index][jndex], g_map[index][jndex + 1]);
					printf("jndex |%d", jndex);
					exit (1);
				}
				jndex++;
			}
			// return ;
		}
		index++;
	}
}

int get_map_size(char *file)
{
	int index;
	int fd;
	char    *line;

	index = 0;
	fd = open(file, O_RDONLY, 0777);
	if (fd == -1)
		exit (1);
	line = get_next_line(fd);
	while (line)
	{
		index++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (index);
}

char    **get_g_map(char *file, int *g_map_size)
{
	int     fd;
	char    **g_map;
	char    *line;
	int     index;

	(*g_map_size) = get_map_size(file);
	g_map = (char **)malloc(sizeof(char *) * (*g_map_size) + 1);
	if (!g_map)
		exit(1);
	fd = open(file, O_RDONLY, 0777);
	if (fd == -1)
		exit (1);
	line = get_next_line(fd);
	index = 0;
	while (line)
	{
		g_map[index] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
		index++;
	}
	return (g_map[index] = NULL, g_map);
}

void    parsing(char *argv[], t_data *data)
{
	char    **g_map;
	int     g_map_size;
	int     index;

	g_map = get_g_map(argv[1], &g_map_size);
	// parsing_map(g_map, data, g_map_size);
	check_map_parameters(g_map, data);
	index = 0;
	while (g_map[index])
	{
		free(g_map[index]);
		index++;
	}
	free(g_map);
	
}
//-------------------------------------- check map parmeters 
void	check_map_parameters(char **map, t_data *data)
{
	int i;
	int	parameters;

	i = 0;
	parameters = 6;
	while(map[i] != NULL)
	{
		if(ft_strncmp(map[i],"NO ", 3) == 0 || ft_strncmp(map[i],"SO ", 3) == 0 || \
		ft_strncmp(map[i],"WE ", 3) == 0 || ft_strncmp(map[i],"EA ", 3) == 0 \
		|| ft_strncmp(map[i],"C ", 2) == 0 || ft_strncmp(map[i],"F ", 2) == 0 && parameters != 0)
		{
			save_parameters_data(map[i], data);
			parameters--;
			i++;
		}
		else if(ft_strncmp(map[i],"\n", 2) == 0)
			i++;
		else if (parameters == 0)
			break;
		else 
		{
			printf("Error by bellakrim parsing\n");
			exit(1);
		}
	}
}
//----------------------------------- 
void	save_parameters_data(char *line, t_data *data)
{
	char **parameters;

	parameters = ft_split(line, ' ');
	if(twod_array_size(parameters) != 2)
	{
		printf("Error by bellakrim parsing\n");
		exit(1);
	}
	if(ft_strncmp(parameters[0], "NO", 2) == 0 || ft_strncmp(parameters[0], "SO", 2) == 0 || \
	ft_strncmp(parameters[0], "WE", 2) == 0 || ft_strncmp(parameters[0], "EA", 2) == 0)
		save_texture(parameters[0], parameters[1], data);
	else if(ft_strncmp(parameters[0], "C", 2) == 0 || ft_strncmp(parameters[0], "F", 2) == 0)
		save_color(parameters[0], parameters[1], data);
}
//---------------------------------------------------- save texture data
void	save_texture(char *texture,char *texture_data, t_data *data)
{
	if(ft_strncmp(texture, "NO", 2) == 0)
		data->no = ft_strdup(texture_data);
	else if(ft_strncmp(texture, "SO", 2) == 0)
		data->so = ft_strdup(texture_data);
	else if(ft_strncmp(texture, "WE", 2) == 0)
		data->we = ft_strdup(texture_data);
	else if(ft_strncmp(texture, "EA", 2) == 0)
		data->ea = ft_strdup(texture_data);
}
//-------------------------------------------------------- save color data
void	save_color(char *color, char *color_data, t_data *data)
{
	int r;
	int g;
	int b;
	char **color_tab;

	color_tab = ft_split(color_data, ',');
	if(twod_array_size(color_tab) != 3)
	{
		printf("Error by bellakrim parsing\n");
		exit(1);
	}
	r = ft_atoi(color_tab[0]);
	g = ft_atoi(color_tab[1]);
	b = ft_atoi(color_tab[2]);
	if(r < 0 || g < 0 || b < 0 || r > 255 || g > 255 || b > 255 || !ft_isalnum(r) || !ft_isalnum(g) || !ft_isalnum(b))
	{
		printf("Error by bellakrim\n");
		exit(1);
	}
	if(ft_strncmp(color, "C", 1) == 0)
	{
		data->c.r = r;
		data->c.g = g;
		data->c.b = b;
	}
	else if (ft_strncmp(color, "F", 1) == 0)
	{
		data->f.r = r;
		data->f.g = g;
		data->f.b = b;
	}
}
//--------------------------------------------- function returns 2d array size 
int twod_array_size(char **tab)
{
	int i;

	i = 0;
	while(tab[i] != NULL)
		i++;
	return (i);
}